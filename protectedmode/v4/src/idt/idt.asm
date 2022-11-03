section .asm

global idt_load
idt_load:
    push ebp    ;start function
    mov ebp, esp

    mov ebx, [ebp+8] ;move the value of the address ebp+8 into ebx, points to our first asm code (push ebp)
    lidt [ebx] ; load idtr_descriptor table

    pop ebp ;end function
    ret