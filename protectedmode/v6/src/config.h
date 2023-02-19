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

#define M_OS_MAX_FILESYSTEMS 12
#define M_OS_MAX_FILE_DESCRIPTORS 512

//
#define M_OS_SECTOR_SIZE 512 //sector size of a normal Harddisk

#define LOGO "                                                                                 @@gg         ,gggggL,                                                            !%@@C       @@@@@@@@@@                                                           .@@@      ]@@@K  $@@@k  ,gggggggw gggg   ggg= ,gggggg   ,gggggg  ,ggg ;gggw    ,@@@C      @@@@Wgg@@@@`g@@@PT]@@@h %@@@  @@@M ]@@@T    ,@@@^  @@@k @@@@@M@@@@   ]@@@T      J@@@@%%%N*T ]@@@C  @@@@  j@@@.@@@C   %@@@@W  @@@@@@@@M ]@@@h  @@@%   J@@$       @@@@        ]@@@kg@@@@K   @@@@@@T      ]@@@M @@@b      @@@@  (@@@M    !%@@g     %%%%         *%@%C]%%%C   ]@@@@    R%@@@%M'   %0@@%N  J%%%K  %%%%                                      ggg@@@M                                                                         #%%PM                                       "

#define M_OS_LOGO 1
#define M_OS_STATUS 1
#endif