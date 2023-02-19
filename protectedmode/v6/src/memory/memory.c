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

int memcmp(void* s1, void* s2, int count) {
    char* c1 = s1;
    char* c2 = s2;
    while(count-- > 0) {
        if (*c1++ != *c2){
            return c1[-1] < c2[-1] ? -1 : 1;;
        }
    }

    return 0;
    
}