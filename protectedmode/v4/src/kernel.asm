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

load_vga_chars:

    mov edi, 0x500000
	;in: edi=4k buffer
	;out: buffer filled with font
	;clear even/odd mode
	mov			dx, 03ceh
	mov			ax, 5
	out			dx, ax
	;map VGA memory to 0A0000h
	mov			ax, 0406h
	out			dx, ax
	;set bitplane 2
	mov			dx, 03c4h
	mov			ax, 0402h
	out			dx, ax
	;clear even/odd mode (the other way, don't ask why)
	mov			ax, 0604h
	out			dx, ax
	;copy charmap
	mov			esi, 0A0000h
	mov			ecx, 256
	;copy 16 bytes to bitmap
.loop:
	movsd
	movsd
	movsd
	movsd
	;skip another 16 bytes
	add			esi, 16
	loop		.loop
	;restore VGA state to normal operation
	mov			ax, 0302h
	out			dx, ax
	mov			ax, 0204h
	out			dx, ax
	mov			dx, 03ceh
	mov			ax, 1005h
	out			dx, ax
	mov			ax, 0E06h
	out			dx, ax

    jmp $ ; endless jump


times 512-($ - $$) db 0 ; for the alignment, 512 % 16 = 0