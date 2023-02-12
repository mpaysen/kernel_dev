#include "idt.h"
#include "config.h"
#include "terminal.h"
#include "memory/memory.h"
#include "io/io.h"
struct idt_desc idt_descriptors[M_OS_TOTAL_INTERRUPS];
struct idtr_desc idtr_descriptor;

// to know the asm code 
extern void idt_load(struct idtr_desc* ptr);
extern void no_interrupt();
extern void idt0();
extern void init21h();

//what to do; by interrupt zero
void idt_zero_handler() {
    print("Devide by zero error\n"); //not println, cause divide zero error wont work with that
    outb(0x20, 0x20);
}

void init21h_handler(){
    print("Keyboard pressed!\n");
    outb(0x20, 0x20);
}

void no_interrupt_handler(){
    outb(0x20, 0x20);
}

//define interrupts, https://wiki.osdev.org/IDT -> Gate Descriptor 
void idt_set(int interrupt_no, void* address) {
    struct idt_desc* desc = &idt_descriptors[interrupt_no]; // &idt_descriptors is the address of the idt_descriptors with the [interrupt no]
    desc->offset_1 = (uint32_t) address & 0x0000ffff;
    desc->selector = KERNEL_CODE_SEG; //CODE_SEG, defined in config.h
    desc->zero = 0x00;
    desc->type_attribute = 0xEE; // bitewise 11101110, lowest 4 bits fot the type, the zero for Storeagesegment, and the 0b11 for Ring 3, last bit set to zero for unused innterups, set to 1
    desc->offset_2 = (uint32_t) address >> 16; 
}

// initialze idt descriptor table
void idt_init() {
    // set the memory for the idt_descriptors clear with zeros
    memset(idt_descriptors, 0, sizeof(idt_descriptors));
    // set the descriptor table limit 
    idtr_descriptor.limit = sizeof(idt_descriptors) - 1;
    // set the base address
    idtr_descriptor.base = (uint32_t) idt_descriptors;

    for (int i = 0; i < M_OS_TOTAL_INTERRUPS; i++) {
        idt_set(i, no_interrupt);
    }

    // set zero interrupt
    idt_set(0, idt0);
    idt_set(0x21, init21h);

    // Load the interrupt descriptor table into memory
    idt_load(&idtr_descriptor);
}