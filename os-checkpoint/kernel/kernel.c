#include "../drivers/screen.h"

void main() {
    clear_screen();
    kprint_at("X", 0, 0);
    kprint_at("This text spans multiple lines", 75, 10);
    kprint_at("This is a line\nbreak", 0, 20);
    kprint("There is a line break");
    kprint_at("What happens when we run out of space?", 45, 24);
}
