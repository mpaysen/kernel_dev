ORG 0
BITS 16
global bpb_disk_info


    jmp short boot_continue
    nop

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


 ; Interrupt 0x00
handle_zero:
    ; Print 'Exception'
    mov si, stringException
    call print
    iret ;interup return

boot_continue:
    jmp 0x7c0:boot ; set Code Segment to Address 0x7c0 and jump to boot

boot:

    cli ; Clear Interrups
    ; Create Origin Address for DataSegment and ExtraSegment, to not relay on the BIOS
    mov ax, 0x7c0 ; set accumulator to 0x7c0
    mov ds, ax ; point accumulator to Data Segment
    mov es, ax ; point extra segment to Data Segment
    ; Create Origin Address for StackSegment and StackPointer, to not relay on the BIOS
    mov ax, 0x00 ; mov 0x00 to accumulator  
    mov ss, ax; mov accumulator into Stack Segment
    mov sp, 0x7c00 ; set stackpointer to 0x7c00
    sti ; Enables Interrups

    ; change interup zero
    mov word[ss:0x00], handle_zero ; using Stack Segment, because ss points to zero in mem and the Interruptvector Table starts at 0x00 in mem
    mov word[ss:0x02], 0x7c0 ; our Segment

    ; read from disk
    mov ah, 2 ; "Read Sector" Command
    mov al, 1 ; Sectors to read (must be nonzero)
    mov ch, 0 ; Set cylinder number to zero
    mov cl, 2 ; Read Sector two
    mov dh, 0 ; Head number
    ; dl (drive number) is alredy set, because were booting from the same disk
    mov bx, buffer ; read the sector to buffer
    int 0x13
    jc errorReadDisk ; jump if carrier to errorReadDisk

    mov si, buffer
    call print

    jmp $ ; endless jump

errorReadDisk:
    mov si, stringFailedSector
    call print
    jmp $ 

print:
    ; move 0 to base register for the BIOS to print something
    mov bx, 0
.loop:
    lodsb   ; load byte into accumulator low and set source index one byte further
    cmp al, 0 ; compare 0x00 with  accumulator low (string 0x00 byte)
    je .done ;  jump if equal
    call print_char
    jmp .loop
.done:   
    ret

print_char:
    mov ah, 0eh ; move 0eh to accumulator high for the BIOS to print something
    int 0x10 ; "call interup 0x10"
    ret

stringException: db 'Exception, cant divide by zero', 13, 10, 0

stringFailedSector: db 'Failed to load sector', 13, 10, 0


times 510-($ - $$) db 0
dw 0xAA55

buffer: ; in mem 0x7c00 + 0x200(512 bytes) (boot sector lenght)