#include "kernel.h"
#include <stdint.h>
#include <stddef.h>

uint16_t* video_mem = 0; //initialize uint16_t video_mem, set to 0
uint16_t terminal_col = 0;
uint16_t terminal_row = 0;

//Make Char and color
uint16_t terminal_make_char(char c, char colour) {
    return (colour << 8) | c; //shift the colour to the highest 8 bits, append with or the char to the lowest 8 bits
}

// output char with coordinates
void terminal_putchar(int x, int y, char c, char colour ) {
    video_mem[(y * VGA_WIDTH) + x] = terminal_make_char(c, colour);
}

void terminal_writechar(char c, char colour) {
    if (c == '\n') {
        terminal_col = 0;
        terminal_row += 1;
        return;
    }
    if ((terminal_row >= VGA_HEIGHT-1) & (terminal_col >= VGA_WIDTH)) {
    terminal_row = 0;
    terminal_col = 0;
    }
    if (terminal_col >= VGA_WIDTH) {
        terminal_col = 0;
        terminal_row += 1;
    }
    terminal_putchar(terminal_col, terminal_row, c, colour);
    terminal_col +=1;
}

void terminal_initialize() { //Clean the Screen
    terminal_col = 0;
    terminal_row = 0;
    video_mem = (uint16_t*)(0xB8000);
    for (int y = 0; y < VGA_HEIGHT; y++) { // HEIGHT
        for (int x = 0; x < VGA_WIDTH; x++) { //WIDTH
            terminal_putchar(x, y, ' ', 0);
        }
    }
}
// get the string lenght
size_t strlen(const char* str) {
    size_t len = 0;
    while(str[len]) {
        len ++;
    }

    return len;
}

void print(const char* str) {
    size_t len = strlen(str);
    for (int i = 0; i < len; i++) {
        terminal_writechar(str[i], 15);
    }
    

}

void kernel_main() {
    terminal_initialize();
    print("Kernel loaded...\nTerminal initiated...\n\nOne System to rule them all, One System to find them,\nOne System to bring them all in the darkness and bind them!");
}
