ORG 0x7c00
BITS 16

CODE_SEG equ gdt_code - gdt_start ; get offset for gdt_code
DATA_SEG equ gdt_data - gdt_start ; get offset for gtd_data

global bpb_disk_info


    jmp short boot_continue ; 0x7c3e
    nop


;----------------------------------------------------------------------------
bpb_disk_info:

    ; Dos 4.0 EBPB (Extended BIOS Parameter Block) 1.44MB floppy
    OEMname:           db    "M:OS.fat"
    bytesPerSector:    dw    512
    sectPerCluster:    db    1
    reservedSectors:   dw    1
    numFAT:            db    2
    numRootDirEntries: dw    224
    numSectors:        dw    2880
    mediaType:         db    0xf0
    numFATsectors:     dw    9
    sectorsPerTrack:   dw    18
    numHeads:          dw    2
    numHiddenSectors:  dd    0
    numSectorsHuge:    dd    0
    driveNum:          db    0
    reserved:          db    0
    signature:         db    0x29
    volumeID:          dd    0x2d7e5a1a
    volumeLabel:       db    "M:OS Loader"
    fileSysType:       db    "FAT12   "
;----------------------------------------------------------------------------

boot_continue:
    jmp 0:boot ; set Code Segment to Address 0x7c0 and jump to boot ; 0x7c3e

boot:

    cli ; Clear Interrups ; 0x7c43:
    ; Create Origin Address for DataSegment and ExtraSegment, to not relay on the BIOS
    mov ax, 0x00 ; set accumulator to 0x7c0
    mov ds, ax ; point accumulator to Data Segment
    mov es, ax ; point extra segment to Data Segment
    ; Create Origin Address for StackSegment and StackPointer, to not relay on the BIOS
    mov ss, ax; mov accumulator into Stack Segment
    mov sp, 0x7c00 ; set stackpointer to 0x7c00
    sti ; Enables Interrups

; init protected mode
.load_protected:

    cli ; Clear Interrups
    lgdt[gtd_descriptor] ; load the Global Descriptor Table ;0x7c52:
    mov eax, cr0
    or eax, 0x1 ; set PE (Protection Enable) bit in CR0 (Control Register 0)
    mov cr0, eax  ;0x7c5e:

    ; Perform far jump to selector CODE_SEG (offset into GDT, pointing at a 32bit PM code segment descriptor) 
    ; to load CS with proper load32 descriptor)
    jmp CODE_SEG:load32 ; jmp to kernel  ;0x7c61 jmp


;----------------------------------------------------------------------------
; GDT (Global Descriptor Table) tells the CPU about memory segments.
gdt_start:
gdt_null:
    dd 0x0
    dd 0x0

; offset 0x8:
gdt_code:   ; CS SHOULD POINT TO THIS
    dw 0xffff ; Segment limit first 0-15 bits
    dw 0x0    ; Base first 0-15 bits
    db 0x0    ; Base 16-23 bits
    db 10011010b   ; Access byte, https://wiki.osdev.org/GDT, FLAG description
    db 11001111b   ; High 4 bit flags and the low 4 bit flags
    db 0x0    ; Base 24-31 bits

; offset 0x10:
gdt_data:     ; DS, SS, ES ,FS, GS
    dw 0xffff ; Segment limit first 0-15 bits
    dw 0x0    ; Base first 0-15 bits
    db 0x0    ; Base 16-23 bits
    db 10010010b   ; Access byte, https://wiki.osdev.org/GDT, FLAG description
    db 11001111b   ; High 4 bit flags and the low 4 bit flags
    db 0x0    ; Base 24-31 bits
gtd_end:

gtd_descriptor:
    dw gtd_end - gdt_start - 1 ; size of the descriptor
    dd gdt_start
;----------------------------------------------------------------------------

[BITS 32]
; protected 32bit mode
load32:
;---------------------------------- VMWare fix, moved from kernel.asm
; load DS, ES, FS, GS, SS, ESP
   mov ax, DATA_SEG
   mov ds, ax
   mov ss, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   mov ebp, 0x00200000
   mov esp, ebp

    ; enable the A20 Line
   in al, 0x92
   or al, 2
   out 0x92, al
;----------------------------------
    ;https://wiki.osdev.org/Memory_Map_(x86)
    ; load Data into memory with lba (Logical Block Address)
    mov eax, 1  ; starting Sector, not 0 cause zero is the boot Sector  ;0x7ca8:
    mov cl, 100 ; for the 100 Sectors, defined in the Makefile
    mov edi, 0x00100000 ; 1 Mebibyte, or 1048576 bytes -> Address where to load the sectors into  ;0x7caf:

    call ata_lba_read ;0x7cb7 -> ret 0x7d15:
;-----------------------------------------------------------------------------

    call check_disk

    jmp CODE_SEG:0x00100000 ; jump to the loaded Data, problem with VMWARE! HERE! ;0x7cbc:      ljmp   $0x8,$0x100000

    ;jmp $ ; endless jump ;0x7cbc

;----------------------------------------------------------------------------
;LBA Driver
ata_lba_read:
    mov ebx, eax ; Beakup the LBA ;0x7cbe

    ; send the highest 8 bits of the lba to the disk controller
    shr eax, 24 ; 32bits - 24bits = 8 btis, shift 24 bits to the right to get th highest 8 bits
    or eax, 0xE0 ; select the master drive, Set bit 6 in al for LBA mode
    mov dx, 0x1F6 ; Port to send drive and bit 24 - 27 of LBA
    out dx, al ; accumulator low with the highest 8 bits ;0x7ccc:
    ; Finished sending the highest 8 bits of the lba

    ; send the total sectors to read
    mov eax, ecx
    mov dx, 0x01F2      ; Port to send number of sectors
    out dx, al
    ; Finished sending the total sectors to read

    ; send bit 0 - 7 of LBA
    mov eax, ebx ; Restore the Backup LBA
    mov dx, 0x1F3 ; Port to send bit 0 - 7 of LBA
    out dx, al
    ; Finished sending of bit 0 - 7 of LBA

    ; send bit 8 - 15 of LBA
    mov eax, ebx ; Restore the Backup LBA
    mov dx, 0x1F4 ; Port to send bit 8 - 15 of LBA
    shr eax, 8 ; shift eax by 8 bits, Get bit 8 - 15 in AL
    out dx, al ;0x7ce4:
    ; Finished sending of send bit 8 - 15 of LBA

    ; send bit 16 - 23 of LBA
    mov eax, ebx ; Restore the Backup LBA
    mov edx, 0x1F5       ; Port to send bit 16 - 23 of LBA
    shr eax, 16          ; Get bit 16 - 23 in AL
    out dx, al
    ; Finished sending of send bit 16 - 23 of LBA

    mov dx, 0x1F7       ; Command port
    mov al, 0x20         ; Read with retry.
    out dx, al

; Read all sectors into memory
.next_sector:
    push ecx ; save the total numbers of sectors we want to read in the stack ;0x7cf7:

; Checking if we need to read
.try_again:
    mov dx, 0x1F7 ; Command port to read
    in al, dx   ; into the al register
    test al, 8  ; the sector buffer requires servicing.
    jz .try_again ; if the test fails try again

; Read 256 words at a time, (256 words are 1 Sector)
    mov ecx, 256
    mov dx, 0x1F0 ; Data port, out ;0x7d0b
    rep insw    ; Input word from I/O port specified in DX into memory location specified in ES:(E)DI
    pop ecx ; get the total numbers of sectors we want to read from the stack
    loop .next_sector ; Decrement count; jump short if count 0
    ; end of reading all sectors into memory
    ret ;0x7d10:
;----------------------------------------------------------------------------

check_disk:
    mov ebx, [0x00100000] ; memory to read first sector of kernel
    cmp ebx, 0x20e611b0 ; first db of sector1 (Signature)
    je .return ;  jump if equal
    mov si, string
    call print
    jmp $
.return:
    ret


print:
    ; move 0xB8000 to Base register to print something
    mov ebx, 0xB8000
.loop:
    lodsb   ; load byte into accumulator low and set source index one byte further
    cmp al, 0 ; compare 0x00 with accumulator low (string 0x00 byte)
    je .done ;  jump if equal
    call print_char
    jmp .loop
.done:    
    ret ; 0x7d27

print_char:
    mov [ebx], al ; move al to ebx[] to print something
    add ebx, 1 ; set the ebx address one further
    mov ah, 0xF; set the color
    mov [ebx], ah ;move al to ebx[] to color something
    add ebx, 1 ; set the ebx address one further
    ret
;----------------------------------------------------------------------------

string: db 'M:OS bootloader cannot read the first sector, or the kernel signature is wrong!              ', 0
times 510-($ - $$) db 0
dw 0xAA55