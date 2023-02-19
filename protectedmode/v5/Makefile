FILES = ./build/kernel.asm.o ./build/kernel.o ./build/terminal.o ./build/idt/idt.asm.o ./build/io/io.asm.o ./build/vga/vga.asm.o ./build/idt/idt.o ./build/memory/memory.o ./build/memory/heap/heap.o ./build/memory/heap/kheap.o ./build/memory/paging/paging.o ./build/memory/paging/paging.asm.o ./build/disk/disk.o ./build/string/string.o ./build/fs/pparser.o ./build/disk/streamer.o
INCLUDES = -I./src
FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc

# win mode: kex --sl -s
# test in gdb (linux): target remote | qemu-system-x86_64 -hda bin/os.bin -S -gdb stdio
# test in gdb (linux): target remote | qemu-system-i386 -hda bin/os.bin -S -gdb stdio
# add-symbol-file in gdb (linux): add-symbol-file build/kernelfull.o 0x100000
# because were loading our kernel into address 0x100000
# vmware gdb (linux) target remote 192.168.144.1:8832
# vmware gdb (win) target remote localhost:8832
# to use vmware debuuging deactivate HYPER-V
# bcdedit /set hypervisorlaunchtype off
# bcdedit /set hypervisorlaunchtype auto



#cmd: "C:\Program Files\Oracle\VirtualBox\VBoxManage" convertdd E:\Programmieren\Kernel_Dev\protectedmode\v5\bin\os.raw E:\Programmieren\Kernel_Dev\protectedmode\v5\bin\os.vmdk --format vmdk


all: ./bin/boot.bin ./bin/kernel.bin # set dependencies
	rm -rf ./bin/os.bin		 # remove os.bin, cause we append boot.bin to it
	dd if=./bin/boot.bin >> ./bin/os.bin
	dd if=./bin/kernel.bin >> ./bin/os.bin
	dd if=/dev/zero bs=512 count=100 >> ./bin/os.bin # 100 Sectores
	cp ./bin/os.bin ./bin/os.img

	dd if=./bin/os.bin bs=512 count=100 >> ./bin/os.raw # 100 Sectores
	dd if=/dev/zero bs=512 count=10000 >> ./bin/os.raw # 100 Sectores

message: ./bin/boot.bin 
	rm -rf ./bin/os.bin		 # remove os.bin, cause we append boot.bin to it
	dd if=./bin/boot.bin >> ./bin/os.bin
	dd if=message.txt >> ./bin/os.bin #message in first sector
	dd if=/dev/zero bs=512 count=100 >> ./bin/os.bin # 100 Sectores

./bin/kernel.bin: $(FILES)
	i686-elf-ld -g -relocatable $(FILES) -o ./build/kernelfull.o
	i686-elf-gcc $(FLAGS) -T  ./src/linker.ld -o ./bin/kernel.bin -ffreestanding ./build/kernelfull.o

./bin/boot.bin: ./src/boot/boot.asm
	nasm -f bin -g ./src/boot/boot.asm -o ./bin/boot.bin # compile boot.asm to ./bin/boot.bin, our Driveimage

./build/kernel.asm.o: ./src/kernel.asm
	nasm -f elf -g ./src/kernel.asm -o ./build/kernel.asm.o # -g for debugging

./build/idt/idt.asm.o: ./src/idt/idt.asm
	nasm -f elf -g ./src/idt/idt.asm -o ./build/idt/idt.asm.o # -g for debugging

./build/io/io.asm.o: ./src/io/io.asm
	nasm -f elf -g ./src/io/io.asm -o ./build/io/io.asm.o # -g for debugging

./build/vga/vga.asm.o: ./src/vga/vga.asm
	nasm -f elf -g ./src/vga/vga.asm -o ./build/vga/vga.asm.o # -g for debugging

./build/kernel.o: ./src/kernel.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -c -std=gnu99 ./src/kernel.c -o ./build/kernel.o 

./build/terminal.o: ./src/terminal.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -c -std=gnu99 ./src/terminal.c -o ./build/terminal.o 

./build/idt/idt.o: ./src/idt/idt.c
	i686-elf-gcc $(INCLUDES) -I./src/idt $(FLAGS) -c -std=gnu99 ./src/idt/idt.c -o ./build/idt/idt.o

./build/memory/memory.o: ./src/memory/memory.c
	i686-elf-gcc $(INCLUDES) -I./src/memory $(FLAGS) -c -std=gnu99 ./src/memory/memory.c -o ./build/memory/memory.o

./build/memory/heap/heap.o: ./src/memory/heap/heap.c
	i686-elf-gcc $(INCLUDES) -I./src/memory/heap $(FLAGS) -c -std=gnu99 ./src/memory/heap/heap.c -o ./build/memory/heap/heap.o

./build/memory/heap/kheap.o: ./src/memory/heap/kheap.c
	i686-elf-gcc $(INCLUDES) -I./src/memory/heap $(FLAGS) -c -std=gnu99 ./src/memory/heap/kheap.c -o ./build/memory/heap/kheap.o

./build/memory/paging/paging.o: ./src/memory/paging/paging.c
	i686-elf-gcc $(INCLUDES) -I./src/memory/paging $(FLAGS) -c -std=gnu99 ./src/memory/paging/paging.c -o ./build/memory/paging/paging.o

./build/memory/paging/paging.asm.o: ./src/memory/paging/paging.asm
	nasm -f elf -g ./src/memory/paging/paging.asm -o ./build/memory/paging/paging.asm.o # -g for debugging

./build/disk/disk.o: ./src/disk/disk.c
	i686-elf-gcc $(INCLUDES) -I./src/disk $(FLAGS) -c -std=gnu99 ./src/disk/disk.c -o ./build/disk/disk.o

./build/fs/pparser.o: ./src/fs/pparser.c
	i686-elf-gcc $(INCLUDES) -I./src/fs $(FLAGS) -c -std=gnu99 ./src/fs/pparser.c -o ./build/fs/pparser.o

./build/string/string.o: ./src/string/string.c
	i686-elf-gcc $(INCLUDES) -I./src/string $(FLAGS) -c -std=gnu99 ./src/string/string.c -o ./build/string/string.o

./build/disk/streamer.o: ./src/disk/streamer.c
	i686-elf-gcc $(INCLUDES) -I./src/disk $(FLAGS) -c -std=gnu99 ./src/disk/streamer.c -o ./build/disk/streamer.o



clean:
	# remove ./bin
	rm -rf ./bin/boot.bin
	rm -rf ./bin/kernel.bin
	rm -rf ./bin/os.bin
	rm -rf ./bin/os.img
	rm -rf ./bin/os.raw
	rm -rf ./bin/os.vmdk
	rm -rf ./bin/os.vdi
	# remove ./build
	rm -rf ./build/kernel.asm.o
	rm -rf ./build/kernelfull.o
	rm -rf ./build/kernel.o
	rm -rf ./build/terminal.o 
	# remove ./build/memory
	rm -rf ./build/memory/memory.o
	rm -rf ./build/memory/heap/heap.o
	rm -rf ./build/memory/heap/kheap.o
	rm -rf ./build/memory/paging/paging.o
	rm -rf ./build/memory/paging/paging.asm.o
	# remove ./build/idt
	rm -rf ./build/idt/idt.o
	rm -rf ./build/idt/idt.asm.o
	# remove ./build/io
	rm -rf ./build/io/io.asm.o
	# remove ./build/disk
	rm -rf ./build/disk/disk.o
	rm -rf ./build/disk/streamer.o
	# remove ./build/string
	rm -rf ./build/string/string.o
	# remove ./build/fs
	rm -rf ./build/fs/pparser.o
	# remove ./build/vga
	rm -rf ./build/vga/vga.asm.o