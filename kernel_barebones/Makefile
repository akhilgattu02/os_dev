#$@: Target file
#$<: First file
#$^: All files


all: run

kernel.bin: kernel_entry.o kernel.o
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.o: kernel.c
	gcc -m32 -c $< -o $@

kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@

boot_sect.bin: bootsect.asm
	nasm $< -o $@

os-image.bin: boot_sect.bin kernel.bin
	cat $^ > $@

run: os-image.bin
	qemu-system-x86_64 $<

clean:
	rm *.bin *.o *.dis

