#include "screen.h"
#include "ports.h"

void clear_screen()
{
	/* Loop through VGA and fill it with empty space to clear screen*/
	char* vga = (char*)VIDEO_ADDRESS;
	for(int i = 0; i < 2 * MAX_ROWS * MAX_COLS; i = i + 2)
	{
		vga[i] = ' ';
		vga[i+1] = 0x0f;
	}
}

void set_cursor_position(int x, int y)
{
	int position = x * MAX_COLS + y;

	/* High bits */
	port_byte_out(0x3D4, 14);
	port_byte_out(0x3D5, (position >> 8) & (0x00FF));

	/* Low bits*/
	port_byte_out(0x3D4, 15);
	port_byte_out(0x3D5, position & (0x00FF));
}

int get_cursor_position()
{
	/* To understand this take position = 0x1234,
	 * High bit: 0x0012 and Low bit: 0x0034,
	 * Hence, we left shift 0x0012 by 8 to get 0x1200
	 * and add 0x0034 to it to get 0x1234
	 *  */
	port_byte_out(0x3D4, 14);
	int position = port_byte_in(0x3D5);
	port_byte_out(0x3D4, 15);
	position = position << 8;
	position += port_byte_in(0x3D5);
	return position;
}

int get_cursor_row(int position)
{
	/* position = row * MAX_COLS + col*/
	int row = position/MAX_COLS;
	return row;
}

int get_cursor_column(int position)
{
	int row = get_cursor_row(position);
	int col = position - (row * MAX_COLS);
	return col;
}

int get_offset(int row, int col)
{
	int position = row * MAX_COLS + col;
	return position;
}

void k_print_at(char* message, int x, int y)
{
	int position = get_offset(x, y);

	/* Offset will be twice of position as VGA stores attribute
	 *  and color for every memory cell.
	 */
	int i = 2*position;
        char* vga = (char*)VIDEO_ADDRESS;
	
        while(message[(i-2*position)/2] != '\0')
        {
		if(i > (2 * MAX_ROWS * MAX_COLS) - 2)
		{
			//vga[2 * MAX_ROWS * MAX_COLS - 2] = 'E';
                        //vga[2 * MAX_ROWS * MAX_COLS - 1] = 0xf4;
			scroll_screen();
			char* init = &message[0];
			char* new_msg = (init + ((i-2*position)/2));
			k_print_at(new_msg, MAX_ROWS - 1, 0);
			break;
		}
                vga[i] = message[(i-2*position)/2];
                vga[i+1] = 0x0f;
                i = i + 2;
        }

}

void k_print(char* message)
{
	k_print_at(message, 0, 0);
}

void scroll_screen()
{
	char* vga = (char*)VIDEO_ADDRESS;
	for(int row = 0; row < MAX_ROWS - 1; row++)
	{
		for(int col = 0; col < MAX_COLS; col++)
		{
			int dest_index = 2 * (row * MAX_COLS + col);
			int src_index = 2 * ((row + 1) * MAX_COLS + col);
			vga[dest_index] = vga[src_index];
			vga[dest_index + 1] = vga[src_index + 1];
		}
	}
	for(int col = 0; col < MAX_COLS; col++)
	{
		int index = (MAX_ROWS-1) * (MAX_COLS) + col;
		vga[2 * index] = '#';
		vga[2 * (index+1)] = 0x0f;
	}
}
