C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c libc/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h libc/*.h)

# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o}

os-image.bin: boot/bootsect.bin kernel.bin
	cat $^ > os-image.bin

kernel.bin: boot/kernel_entry.o ${OBJ}
	ld -m elf_i386 -T linker.ld -o $@ $^ --oformat binary

kernel.elf: boot/kernel_entry.o ${OBJ}
	ld -m elf_i386 -T linker.ld -o $@ $^

%.o : %.c ${HEADERS}
	gcc -g -m32 -ffreestanding -fno-pic -fno-stack-protector -nostdlib -c $< -o $@

%.o : %.asm
	nasm -f elf32 $< -o $@

%.bin : %.asm
	nasm -f bin $< -o $@


run: os-image.bin
	qemu-system-i386 -fda os-image.bin

debug: os-image.bin kernel.elf
	qemu-system-i386 -s -fda os-image.bin &
	gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o cpu/*.o libc/*.o

commit:
	git add .
	git commit 
	git push origin


