[org 0x7c00]
KERNEL_OFFSET equ 0x1000;

 mov [BOOT_DRIVE], dl;BIOS
 mov bp, 0x9000;
 mov sp, bp;
 
 mov bx, MSG_REAL_MODE_K;
 call print
 call print_nl
 
 call load_kernel;
 call switch_to_pm;
 jmp 0x08:BEGIN_PM; 

%include "../bootsector_barebones/print_hello/print_string.asm"
%include "../bootsector_barebones/bootsector_segmentation/bios_read.asm"
%include "../thirty_two_bit_mode/gdt.asm"
%include "../thirty_two_bit_mode/32_bit_print.asm"
%include "../thirty_two_bit_mode/32_bit_pm.asm"


[bits 16]
load_kernel:
 mov bx, MSG_LOAD_KERNEL_K;
 call print
 call print_nl

 mov bx, KERNEL_OFFSET;
 mov dh, 2;
 mov dl, [BOOT_DRIVE];
 call disk_load;
 ret

[bits 32]
BEGIN_PM:
 mov ebx, MSG_PROT_MODE_K;
 call print_string_pm;
 call KERNEL_OFFSET;
 jmp $

  

BOOT_DRIVE:
  db 0;
MSG_REAL_MODE_K:
  db "Started in 16 bit mode fucker!";
MSG_PROT_MODE_K:
  db "Started in 32 bit mode fucker!";
MSG_LOAD_KERNEL_K:
  db "Kernel loaded fucker!";

times 510 - ($ - $$) db 0
dw 0xaa55
