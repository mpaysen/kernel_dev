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

bool isdigit(char c) {
    return c >= 48 && c <= 56;
}

int tonumericdigit(char c) {
    return c - 48;
}