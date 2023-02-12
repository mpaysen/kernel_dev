#include "memory.h"


// set clean memory
void* memset(void* ptr, int c, size_t size) {
    // set the memory address
    char* c_ptr = (char*) ptr;
    // reserve the space in memory with c
    for (int i = 0; i < size; i++) {
        c_ptr[i] = (char) c;
    }
    return ptr;
}