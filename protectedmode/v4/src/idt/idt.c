#include "idt.h"
#include "config.h"
#include "kernel.h"
#include "memory/memory.h"
struct idt_desc idt_descriptors[M_OS_TOTAL_INTERRUPS];
struct idtr_desc idtr_descriptor;

extern void idt_load(struct idtr_desc* ptr);

void idt_zero() {
    print("Devide by zero error\n");
}

//define interrupts, https://wiki.osdev.org/IDT -> Gate Descriptor 
void idt_set(int interrupt_no, void* address) {
    struct idt_desc* desc = &idt_descriptors[interrupt_no]; // &idt_descriptors is the address of the idt_descriptors
    desc->offset_1 = (uint32_t) address & 0x0000ffff;
    desc->selector = KERNEL_CODE_SEG; //Code_SEG
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

    // set zero interrupt
    idt_set(0, idt_zero);

    // Load the interrupt descriptor table into memory
    idt_load(&idtr_descriptor);
}