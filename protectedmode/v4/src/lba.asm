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
    ret ;0x7d15:
;----------------------------------------------------------------------------