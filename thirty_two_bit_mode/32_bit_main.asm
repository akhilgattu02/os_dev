[org 0x7c00]
 
 mov bp, 0x9000
 mov sp, bp

 mov bx, MSG_REAL_MODE
 call print
 call print_nl
 call switch_to_pm
 jmp $

%include "../bootsector_barebones/bootsector_segmentation/print_string.asm"
%include "gdt.asm"
%include "32_bit_print.asm"
%include "32_bit_pm.asm"

[bits 32]

BEGIN_PM:
 mov ebx, MSG_PROT_MODE
 call print_string_pm
 jmp $

MSG_REAL_MODE db "Started in 16 bit mode!", 0
MSG_PROT_MODE db "Started in 32 bit mode!", 0

times 510 - ($ - $$) db 0 
dw 0xaa55
 
