section .asm

global load_vga_chars
global restore_vga

;https://www.scs.stanford.edu/22wi-cs212/pintos/specs/freevga/vga/graphreg.htm
;https://www.scs.stanford.edu/22wi-cs212/pintos/specs/freevga/vga/seqreg.htm

load_vga_chars:
	push ebp
    mov ebp, esp

    xor eax, eax ;zero the eax register
    mov eax, [ebp + 8]
	mov edi, eax ;set address
	;in: edi=4k buffer
	;out: buffer filled with font
	;clear even/odd mode
    MOV DX, 0x3C4
    MOV AX, 0x0402          ; seq.mapmask = !0, !1, 2, !3
    OUT DX, AX

    MOV AX, 0x0604          ; seq.memmode = O/E off, chain4 off, ext on
    OUT DX, AX

    MOV DX, 0x3CE
    MOV AX, 0x1005          ; gx.modereg = !256, !shift, !OE, writemode_0
    OUT DX, AX
    MOV AX, 0x0C06          ; gx.miscreg = map_b8000, !HostOE, !graphics
    OUT DX, AX
	;copy charmap
	mov			esi, 0xB8000
	mov			ecx, 256
	;copy 16 bytes to bitmap
.b:	
	movsd
	movsd
	movsd
	movsd
	;skip another 16 bytes
	add			esi, 16
	loop	.b

	pop ebp
    ret

restore_vga:
	;restore VGA state to normal operation
	mov			ax, 0x0302
	out			dx, ax
	mov			ax, 0x0204
	out			dx, ax
	mov			dx, 0x03ce
	mov			ax, 0x1005
	out			dx, ax
	mov			ax, 0x0E06
	out			dx, ax
	ret