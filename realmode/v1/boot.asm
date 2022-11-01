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
    mov ds, ax ; move accumulator to Data Segment
    mov es, ax
    ; Create Origin Address for StackSegment and StackPointer, to not relay on the BIOS
    mov ax, 0x00 ; mov 0x00 to accumulator  
    mov ss, ax; mov accumulator into Stack Segment
    mov sp, 0x7c00 ; set stackpointer to 0x7c00
    sti ; Enables Interrups

    ; change interup zero
    mov word[ss:0x00], handle_zero ; using Stack Segment, because ss points to zero in mem and the Interruptvector Table starts at 0x00 in mem
    mov word[ss:0x02], 0x7c0 ; our Segment

    ; move messageHello in source index
    mov si, messageHello
    call print
    ; set counter low to 0x00
    mov cl, 0

.loopMats:
    mov si, messageMats
    call print
    cmp cl, 0x9 ; compare counter low to 0x9
    je .doneMats ; jump if equal
    add cl, 1   ; add ont to counter low
    jmp .loopMats 
.doneMats:
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

messageHello: db 'Willkommen im M:OS Bootloader!', 13, 10, 0 ; String with newline (13 ,10) and zero byte
messageMats: db 'Hello Mats!', 13, 10, 0
stringException: db 'Exception', 13, 10, 0

times 510-($ - $$) db 0
dw 0xAA55