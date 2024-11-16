[org 0x7c00]
mov ah, 0x0e
mov bx, test_label
mov al, [change_label]
mov [bx], al 
mov al, [test_label]

int 0x10

test_label:
 db "X"

change_label:
 db "F"

jmp $

times 510 - ($ - $$) db 0
dw 0xaa55
