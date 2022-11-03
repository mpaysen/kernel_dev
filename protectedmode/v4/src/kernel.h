#ifndef KERNEL_H
#define KERNEL_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 24 // 0 -> 24 = 25

void kernel_main();
void print(const char* str);
void println(const char* str);

#endif