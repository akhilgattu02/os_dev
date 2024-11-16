[org 0x7c00]
mov ah, 0x0e;
mov bx, def_msg + 6;
mov dx, bx;
mov al, [dx];
int 0x10;

jmp $

def_msg:
 db "Xander!", 0

the_secret:
 db "F"

times 510 - ($ - $$) db 0
dw 0xaa55


