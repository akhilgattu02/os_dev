[bits 32]
[extern main] ; Must have same name as kernel.c 'main' function
call main ; Calls the C function
jmp $
