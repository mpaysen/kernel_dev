#include "kernel.h"
#include "terminal.h"
#include <idt/idt.h>
#include "config.h"
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"
#include "disk/disk.h"
#include "fs/pparser.h"
#include "disk/streamer.h"
//#include "vga/vga.h"
//#include "memory/memory.h"
extern void problem();


static struct paging_4gb_chunk* kernel_chunk = 0;
void kernel_main() {
    //Initialize the terminal
    terminal_initialize();

    if(M_OS_LOGO) {
    print(LOGO);
    }

    if(M_OS_STATUS) {
    println("Kernel loaded...");
    println("Terminal initialized...");
    }

    //Initialize the heap
    kheap_init();
    if(M_OS_STATUS) {
    println("Kernel Heap initialized...");
    }
    //Search and initialize Harddisks
    disk_search_and_init();
    if(M_OS_STATUS) {
    println("Harddisks initialized...");
    }
    //Initialize the interrupt descriptor table
    idt_init();
    if(M_OS_STATUS) {
    println("Interrupt Descriptor Table initialized...");
    }
    //setup Paging
    kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);

    //Swich to kernel paging chunk
    paging_switch(paging_4gb_chunk_get_directory(kernel_chunk));

    //enable paging
    enable_paging();
    if(M_OS_STATUS) {
    println("Paging initialized...");
    }
    // enable the system interrupts
    enable_interrupts(); 
    if(M_OS_STATUS) {
    println("Interrupts enabled...");
    }
    if(M_OS_LOGO) {
    println("");
    println("");
    println("One System to rule them all, One System to find them,");
    println("One System to bring them all in the darkness and bind them!");
    }
    // struct path_root* root_path = pathparser_parse("0:/bin/shell.bin", NULL);

    struct disk_stream* stream = disk_stream_new(0);
    diskstreamer_seek(stream, 0x201);
    unsigned char c = 0;
    diskstreamer_read(stream, &c, 1);
    

    //void* ptr = (char*) 0x1000;
    //memset(ptr, 0, 4096);
    //load_vga_chars(ptr);
    //restore_vga();
    //println("readed VGA...");
    //problem();
    //print("FFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGGFFFFFHHHHHAAAAAGGGGG");

}