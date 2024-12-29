#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25 
#define MAX_COLS 80

void clear_screen();
void set_cursor_position(int x, int y);
int get_cursor_position();
int get_cursor_row(int position);
int get_cursor_column(int position);

void k_print(char* message);
void k_print_at(char* message, int x, int y);
void scroll_screen();
