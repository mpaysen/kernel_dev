#include "string.h"

int strlen(const char* ptr) {
    int i = 0;
    while(*ptr != 0){ //look for the zero byte, terminator
        i++;
        ptr += 1;
    }

    return i;
}

int strnlen(const char* ptr, int max) {
    int i = 0;
    for (i = 0; i < max; i++) {
        if (ptr[i] == 0) { //look for the zero byte, terminator
            break; 
        }
    }

    return i;
}

char* strcpy(char* dest, const char* src) {

    char* res = dest;
    while (*src != 0)
    {
        *dest = *src;
        src +=1;
        dest += 1;
    }

    *dest = 0x00;

    return res;
    
}

bool isdigit(char c) {
    return c >= 48 && c <= 56;
}

int tonumericdigit(char c) {
    return c - 48;
}