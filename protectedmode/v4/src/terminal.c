#include "terminal.h"
#include <stdint.h>
#include <stddef.h>

uint16_t* video_mem = 0; //initialize uint16_t video_mem, set to 0
uint16_t terminal_x = 0; //initialize uint16_t terminal_x, for the x cordinate 
uint16_t terminal_y = 0; //initialize uint16_t terminal_y, for the y cordinate 

//Make Char and color
uint16_t terminal_make_char(char c, char colour) {
    return (colour << 8) | c; //shift the colour to the highest 8 bits, append with or the char to the lowest 8 bits
}

// output char with coordinates
void terminal_putchar(int x, int y, char c, char colour ) {
    //x for the terminal_x
    //y for the terminal_y
    video_mem[(y * VGA_WIDTH) + x] = terminal_make_char(c, colour);
}



// write char and set the row and or col higher,
// execute newline char with new row
void terminal_writechar(char c, char colour) {
    // newline char definition
    if ((c == '\n') ) {
        terminal_x = 0;
        terminal_y += 1;
        return;
    }
    // set x and y to zero if the end of terminal is reached
    if ((terminal_x >= VGA_WIDTH) & (terminal_y >= VGA_HEIGHT)) {
        terminal_x = 0;
        terminal_y = 0;
    }
    // set the row one higher if the end of the terminal line is reached
    if (terminal_x >= VGA_WIDTH) {
        terminal_x = 0;
        terminal_y += 1;
    }
    //put the char on the current x and y position
    terminal_putchar(terminal_x, terminal_y, c, colour);
    terminal_x +=1;
}

//Clear the Screen and initialize the video mem address
void terminal_initialize() { //Clear the Screen
    terminal_x = 0;
    terminal_y = 0;
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
// print all chars of a str with the terminal_writechar function 
void print(const char* str) {
    size_t len = strlen(str);
    for (int i = 0; i < len; i++) {
        terminal_writechar(str[i], 15);
    }
    

}
// print all chars of a str with the terminal_writechar function and append a new line char
void println(const char* str) {
    print(str);
    terminal_writechar('\n', 0);

}