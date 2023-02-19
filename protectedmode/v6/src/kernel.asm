[BITS 32] 
; no "section .asm", because we need this file in the .text section, to load this code first into memory
global _start
global problem
extern kernel_main ; extern function in kernel.c

CODE_SEG equ 0x8 ; offset for gdt_code
DATA_SEG equ 0x10 ; offset for gdt_data

_start:
;-----moved to boot.asm--------------- ;because VMWare fix in boot.asm
;    ; load DS, ES, FS, GS, SS, ESP
   ;mov ax, DATA_SEG
   ;mov ds, ax
   ;mov ss, ax
   ;mov es, ax
   ;mov fs, ax
   ;mov gs, ax

   ;mov ebp, 0x00200000
   ;mov esp, ebp

    ; enable the A20 Line
   ;in al, 0x92
   ;or al, 2
   ;out 0x92, al
;----------------------------------

; Remap the master PIC
	mov al, 00010001b
	out 0x20, al ; Tell master PIC

	mov al, 0x20 ; Interrupt 0x20 is where master ISR should start
	out 0x21, al

	mov al, 00000001b
	out 0x21, al
; End remap of the master PIC

    call kernel_main

    jmp $ ; endless jump

problem:
	mov eax, 0
	div eax
	ret


times 512-($ - $$) db 0 ; for the alignment, 512 % 16 = 0