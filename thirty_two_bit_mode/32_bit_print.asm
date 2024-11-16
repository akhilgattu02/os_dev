[bits 32]

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f
SCREEN_WIDTH_BYTES equ 160  ; 80 characters * 2 bytes per character


;Prints a null terminated string pointed by edx
print_string_pm:
 pusha
 mov edx, VIDEO_MEMORY ;Set edx to start of video mem

print_string_pm_loop:
 mov al, [ebx];
 mov ah, WHITE_ON_BLACK;
 cmp al, 0
 je print_done
 
 mov [edx], ax;
 add ebx, 1;
 add edx, 2;
 jmp print_string_pm_loop;
 

print_done:

 popa
 ret

 

