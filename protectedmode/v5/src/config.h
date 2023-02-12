#ifndef CONFIG_H
#define CONFIG_H
#define KERNEL_CODE_SEG 0x08
#define KERNEL_DATA_SEG 0x10
#define M_OS_TOTAL_INTERRUPS 512

// 100MB heap size
#define M_OS_HEAP_SIZE_BYTES 104857600
#define M_OS_HEAP_BLOCK_SIZE 4096
#define M_OS_HEAP_ADDRESS 0x01000000
#define M_OS_HEAP_TABLE_ADDRESS 0x00007E00

//
#define M_OS_SECTOR_SIZE 512 //secctor size of a normal Harddisk
#endif