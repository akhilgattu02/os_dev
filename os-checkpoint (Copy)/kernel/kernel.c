#include "../drivers/ports.h"
#include "../drivers/screen.h"

void main() {
    clear_screen();
    char* message = "Have good sex idiot!";
    k_print_at(message, 0, 0);
    k_print_at(message, 24, 0);
    k_print_at(message, 24, 75);
    //int position = get_cursor_position();
    //int row = get_cursor_row(position);
    //int col = get_cursor_column(position);
    for(int i = 0; i < MAX_COLS; i++)
    {
	    k_print_at("F", 0, i);
    }
    for(int i = 1; i < MAX_ROWS; i++)
    {
	    for(int j = 0; j < MAX_COLS; j++)
	    {
		    k_print_at("A", i, j);
	    }
    }
   scroll_screen();
}
