#include "kernel.h"
#include "terminal.h"
#include <idt/idt.h>

void kernel_main() {
    terminal_initialize();
    println("Kernel loaded...");
    println("Terminal initialized...");
    idt_init();
    println("Interrupt Descriptor Table initialized...");
    println("");
    println("One System to rule them all, One System to find them,");
    println("One System to bring them all in the darkness and bind them!");
    //terminal_initialize();
    //print("FFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGTTTTT");


    // Initialize the interrupt descriptor table

}
