#ifndef VGA_H
#define VGA_H

#include <stdint.h>
#include <stddef.h>

void load_vga_chars(uint32_t* port);
void restore_vga();
#endif