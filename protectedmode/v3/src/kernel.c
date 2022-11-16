#include "kernel.h"

void kernel_main() {

    char* video_mem = (char*)(0xB8000); //createt a pointer to the absolute Address in Memory
    video_mem[0] = 0x41;
    //video_mem[1] = 0x04;
    video_mem[1] = 0x04;

}
