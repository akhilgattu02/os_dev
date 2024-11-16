mov bx , 11; bx = 11

cmp bx , 4

jle less_than_4; If bx <= 4, jump to that function.

cmp bx, 40 

jl less_than_40; If bx < 40, jump to that function.

mov al, 'C'; ;If none of them work, execute this line.

jmp the_end;


less_than_4:
  mov al, 'A';
  jmp the_end	

less_than_40:
  mov al, 'B';
  jmp the_end

the_end:

mov ah, 0x0e;
int 0x10;
jmp $;

times 510 - ($ - $$) db 0;
dw 0xaa55;
