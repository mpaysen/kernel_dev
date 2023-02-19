section .asm

extern no_interrupt_handler
extern idt_zero_handler
extern init21h_handler

global no_interrupt
global idt0
global init21h

global enable_interrupts
global disable_interrupts
global idt_load


enable_interrupts:
    sti
    ret

disable_interrupts:
    cli
    ret

idt_load:
    push ebp    ;start function
    mov ebp, esp

    mov ebx, [ebp+8] ;move the value of the address ebp+8 into ebx, points to the first asm code (push ebp)
    lidt [ebx] ; load idtr_descriptor table

    pop ebp ;end function
    ret

no_interrupt:
    cli
    pushad
    call no_interrupt_handler
    popad
    sti
    iret

;Zero Interupt Wrapper
idt0:
    cli
    pushad
    call idt_zero_handler
    popad
    sti
    iret

;Keyboard Interupt Wrapper
init21h:
    cli
    pushad
    call init21h_handler
    popad
    sti
    iret
