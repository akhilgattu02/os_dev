# Get all source files
C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h)

# Convert source files to object files
OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o} 

# Final OS binary
os-image.bin: boot/bootsect.bin kernel.bin
	cat $^ > os-image.bin

# Kernel binary (flat binary format)
kernel.bin: boot/kernel_entry.o ${OBJ}
	ld -m elf_i386 -T linker.ld -o $@ $^ --oformat binary

# Kernel ELF (for debugging)
kernel.elf: boot/kernel_entry.o ${OBJ}
	ld -m elf_i386 -T linker.ld -o $@

# Compile C files
%.o : %.c ${HEADERS}
	gcc -g -m32 -ffreestanding -fno-pic -fno-stack-protector -c $< -o $@

# Compile Assembly files
%.o : %.asm
	nasm -f elf32 $< -o $@

# Assemble bootloader and other raw binary files
%.bin : %.asm
	nasm -f bin $< -o $@

# Run in QEMU
run: os-image.bin
	qemu-system-i386 -no-reboot -fda os-image.bin

# Debug in QEMU with GDB
debug: os-image.bin kernel.elf
	qemu-system-i386 -s -S -fda os-image.bin &
	gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Clean build files
clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o cpu/*.o
