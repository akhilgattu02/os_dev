[bits 32]
[extern kernel_main] ; Must have same name as kernel.c 'main' function
call kernel_main ; Calls the C function
jmp $
