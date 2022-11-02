[BITS 32] 
; no "section .asm", because we need this file in the .text section, to load this code first into memory
global _start
extern kernel_main ; extern function in kernel.c

CODE_SEG equ 0x8 ; offset for gdt_code
DATA_SEG equ 0x10 ; offset for gdt_data

_start:
;-----moved to boot.asm---------------
;    ; load DS, ES, FS, GS, SS, ESP
;    mov ax, DATA_SEG
;    mov ds, ax
;    mov ss, ax
;    mov es, ax
;    mov fs, ax
;    mov gs, ax
;
;    mov ebp, 0x00200000
;    mov esp, ebp
;
;    ; enable the A20 Line
;    in al, 0x92
;    or al, 2
;    out 0x92, al
;----------------------------------
    call kernel_main


    jmp $ ; endless jump

times 512-($ - $$) db 0 ; for the alignment, 512 % 16 = 0