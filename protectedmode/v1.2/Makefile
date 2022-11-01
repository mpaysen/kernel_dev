all:
	nasm -f bin boot.asm -o boot.bin # compile boot.asm to boot.bin, our Driveimage
	cp boot.bin boot.img
	# dd if=message.txt >> boot.bin	 # set message content in the next 512 byte sector (2)
	# dd if=/dev/zero bs=512 count=1 >> boot.bin # append 512 bytes with zeros