[org 0x7c00]
  mov bx, HELLO_MSG;
  call print
  call print_nl

  mov bx, BYE_MSG;
  call print
  call print_nl
  
  mov dx, 0x710f
  call print_hex
  jmp $

%include "print_string.asm"
%include "print_hex.asm"
HELLO_MSG:
 db "Hi, bitch!", 0;

BYE_MSG:
 db "Bye, bitch!", 0;  

 times 510 - ($-$$) db 0
 dw 0xaa55  
