[BITS 32]

section .asm

global paging_load_directory
global enable_paging

paging_load_directory:
    push ebp
    mov  ebp, esp

    mov eax, [ebp + 8] ;move the pointer Value (the directory) into eax
    mov cr3, eax ;set directory

    pop ebp ;return from function
    ret

enable_paging:
    push ebp
    mov  ebp, esp

    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax

    pop ebp ;return from function
    ret