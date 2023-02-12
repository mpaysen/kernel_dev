#include "kernel.h"
#include "terminal.h"
#include <idt/idt.h>
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"
#include "disk/disk.h"
extern void problem();


static struct paging_4gb_chunk* kernel_chunk = 0;
void kernel_main() {
    //Initialize the terminal
    terminal_initialize();
    println("Kernel loaded...");
    println("Terminal initialized...");
    
    //Initialize the heap
    kheap_init();
    println("Kernel Heap initialized...");

    //Search and initialize Harddisks
    disk_search_and_init();
    println("Harddisks initialized...");

    //Initialize the interrupt descriptor table
    idt_init();
    println("Interrupt Descriptor Table initialized...");

    //setup Paging
    kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);

    //Swich to kernel paging chunk
    paging_switch(paging_4gb_chunk_get_directory(kernel_chunk));

    //enable paging
    enable_paging();
    println("Paging initialized...");

    // enable the system interrupts
    enable_interrupts(); 
    println("Interrupts enabled...");

    println("");
    println("One System to rule them all, One System to find them,");
    println("One System to bring them all in the darkness and bind them!");
    //terminal_initialize();
    //problem();
    //print("FFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGTTTTT");
}
