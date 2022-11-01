ORG 0x7c00
BITS 16

CODE_SEG equ gdt_code - gdt_start ; get offset for gdt_code
DATA_SEG equ gdt_data - gdt_start ; get offset for gtd_data

global bpb_disk_info


    jmp short boot_continue
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
    jmp 0:boot ; set Code Segment to Address 0x7c0 and jump to boot

boot:

    cli ; Clear Interrups
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
    lgdt[gtd_descriptor] ; load the Global Descriptor Table
    mov eax, cr0
    or eax, 0x1 ; set PE (Protection Enable) bit in CR0 (Control Register 0)
    mov cr0, eax

    ; Perform far jump to selector CODE_SEG (offset into GDT, pointing at a 32bit PM code segment descriptor) 
    ; to load CS with proper load32 descriptor)
    jmp CODE_SEG:load32

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
; win mode: kex --sl -s
; test in gdb (linux): target remote | qemu-system-x86_64 -hda boot.bin -S -gdb stdio


[BITS 32]
load32:
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

    jmp $ ; endless jump

times 510-($ - $$) db 0
dw 0xAA55