#include "disk.h"
#include "io/io.h"
#include "status.h"
#include "config.h"
#include "memory/memory.h"

//https://wiki.osdev.org/ATA_read/write_sectors


struct disk disk; //represents the primary hard disk

int disk_read_sector(int lba, int total, void * buf){ // read in boot.asm, there is the same code in asm
    outb(0x1F6, (lba >> 24) | 0xE0); // prmary master disk (0xE0) and sector
    outb(0x1F2, total); // total number of sectors to read
    outb(0x1F3, (unsigned char)(lba & 0xff));
    outb(0x1F4, (unsigned char)(lba >> 8));
    outb(0x1F5, (unsigned char)(lba >> 16));
    outb(0x1F7, 0x20);

    unsigned short* ptr = (unsigned short*) buf; //short, brause we read a word aka. two bytes
    for (int b = 0; b < total; b++){
        // Wait for the buffer to be ready
        char c = insb(0x1F7); //read from the bus port 0x1F7
        while(!(c & 0x08)){ //the sector buffer requires servicing.
            c = insb(0x1F7);
        }

        //copy from gard disk to memory
        for (int i = 0; i < 256; i++) {
            *ptr = insb(0x1F0); //Data port, out to buf
            ptr++;
        }
    }
    return 0;
}

void disk_search_and_init(){

    memset(&disk, 0, sizeof(disk));
    disk.type = M_OS_DISK_TYPE_REAL;
    disk.sector_size = M_OS_SECTOR_SIZE;

}

struct disk* disk_get(int index){
    if (index != 0){
        return 0;
    }
    return &disk;
};

int disk_read_block(struct disk* idisk, unsigned int lba, int total, void* buf){

    if (idisk != &disk){
        return -M_OS_IO_ERROR;
    }

    return disk_read_sector(lba, total, buf);

};

