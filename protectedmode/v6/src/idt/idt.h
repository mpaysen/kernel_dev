#ifndef IDT_H
#define IDT_H


//define interrupt struct, https://wiki.osdev.org/IDT -> Gate Descriptor 
#include <stdint.h>
struct idt_desc {
    uint16_t offset_1; // Offset bits 0 - 15
    uint16_t selector; // Selector thats in our GDT
    uint8_t zero; // Zero Byte for nothing @ all
    uint8_t type_attribute; // Descriptor Type and attributes
    uint16_t offset_2; // Offset bits 16 - 31
} __attribute__((packed));


struct idtr_desc {
    uint16_t limit; // Size of descriptor table -1
    uint32_t base; // Base address of the start of the table
} __attribute__((packed));

void idt_init();
void enable_interrupts();
void disable_interrupts();

#endif