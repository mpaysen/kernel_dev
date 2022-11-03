#ifndef TERMINAL_H
#define TERMINAL_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 24 // 0 -> 24 = 25


void print(const char* str);
void println(const char* str);
void terminal_initialize();

#endif