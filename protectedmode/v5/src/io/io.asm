section .asm
;https://c9x.me/x86/html/file_module_x86_id_139.html
global insb
global insw
global outb
global outw
; the eax register is always the return value in asm and c

insb:
    push ebp
    mov ebp, esp

    xor eax, eax ;zero the eax register
    mov edx, [ebp + 8] ;specify th port (short) move it into the lower 8bits from edx
    in al, dx ;load the byte from the port in dx (lower 8bits from edx) into al (lower 8bits from eax)

    pop ebp
    ret

insw:
    push ebp
    mov ebp, esp

    xor eax, eax ;zero the eax register
    mov edx, [ebp + 8] ;specify th port (short) move it into the lower 8bits from edx
    in ax, dx ;load the byte from the port in dx (lower 8bits from edx) into ax (lower 16bits from eax)

    pop ebp
    ret

outb:
    push ebp
    mov ebp, esp

    mov eax, [ebp + 12]
    mov edx, [ebp + 8] ;specify th port (short) move it into the lower 8bits from edx
    out dx, al ; Output byte in AL to I/O port address in DX.

    pop ebp
    ret

outw:
    push ebp
    mov ebp, esp

    mov eax, [ebp + 12]
    mov edx, [ebp + 8] ;specify th port (short) move it into the lower 8bits from edx
    out dx, ax ; Output byte in AX to I/O port address in DX.

    pop ebp
    ret