FILES = ./build/kernel.asm.o ./build/kernel.o 
INCLUDES = -I./src
FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc

# win mode: kex --sl -s
# test in gdb (linux): target remote | qemu-system-x86_64 -hda bin/os.bin -S -gdb stdio
# add-symbol-file in gdb (linux): add-symbol-file build/kernelfull.o 0x100000
# because were loading our kernel into address 0x100000
# vmware gdb (linux) target remote 192.168.144.1:8832
# vmware gdb (win) target remote localhost:8832
# to use vmware debuuging deactivate HYPER-V
# bcdedit /set hypervisorlaunchtype off
# bcdedit /set hypervisorlaunchtype auto



#cmd: "C:\Program Files\Oracle\VirtualBox\VBoxManage" convertdd E:\Programmieren\Kernel_Dev\protectedmode\v4\bin\os.raw E:\Programmieren\Kernel_Dev\protectedmode\v4\bin\os.vmdk --format vmdk


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

./build/kernel.o: ./src/kernel.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -c -std=gnu99 ./src/kernel.c -o ./build/kernel.o 

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