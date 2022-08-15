#include "screen.h"
#include "../cpu/ports.h"
#include "../libc/mem.h"
#include "../libc/function.h"

int	get_screen_offset(int col, int row)
{
	return (2 * (row * MAX_COLS + col));
}

int	get_cursor(void)
{
	int	offset;

	port_byte_out(REG_SCREEN_CTRL, 14);
	offset = port_byte_in(REG_SCREEN_DATA) << 8;
	port_byte_out(REG_SCREEN_CTRL, 15);
	offset += port_byte_in(REG_SCREEN_DATA);
	return (offset * 2);
}

void	set_cursor(int offset)
{
	offset /= 2;
	port_byte_out(REG_SCREEN_CTRL, 14);
	port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
	port_byte_out(REG_SCREEN_CTRL, 15);
	port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));

}

int	get_offset_row(int offset)
{
	return (offset / (2 * MAX_COLS));
}

int	get_offset_col(int offset)
{
	return ((offset - (get_offset_row(offset) * 2 * MAX_COLS)) / 2);
}


int	handle_scrolling(int cursor_offset)
{
	int		i;
	char	*last_line;

	if (cursor_offset < MAX_ROWS * MAX_COLS * 2)
		return (cursor_offset);
	i = 0;
	while (++i < MAX_ROWS)
	{
		memory_copy(get_screen_offset(0, i) + (char *)VIDEO_ADDRESS,
					get_screen_offset(0, i - 1) + (char *)VIDEO_ADDRESS,
					MAX_COLS * 2);
	}
	i = -1;
	last_line = get_screen_offset(0, MAX_ROWS - 1) + (char *)VIDEO_ADDRESS;
	while (++i < MAX_COLS * 2)
		last_line[i] = 0;
	cursor_offset -= 2 * MAX_COLS;
	return (cursor_offset);
}

int	print_char(char character, int col, int row, char attribute_byte)
{
	char	*vidmem = (char *)VIDEO_ADDRESS;
	int		offset;

	if (!attribute_byte)
		attribute_byte = WHITE_ON_BLACK;
	if (col >= 0 && row >= 0)
		offset = get_screen_offset(col, row);
	else
		offset = get_cursor();
	if (character == '\n')
	{
		row = get_offset_row(offset);
		offset = get_screen_offset(0, row + 1);
	}
	else
	{
		vidmem[offset] = character;
		vidmem[offset + 1] = attribute_byte;
		offset += 2;
	}
	offset = handle_scrolling(offset);
	set_cursor(offset);
	return (offset);
}

void	print_at(char *message, int col, int row)
{
	int	i;
	int	offset;

	if (col >= 0 && row >= 0)
		offset = get_screen_offset(col, row);
	else
	{
		offset = get_cursor();
		row = get_offset_row(offset);
		col = get_offset_col(offset);
	}
	i = 0;
	while (message[i])
	{
		offset = print_char(message[i++], col, row, WHITE_ON_BLACK);
		row = get_offset_row(offset);
		col = get_offset_col(offset);
	}
}

void	print(char *message)
{
	print_at(message, -1, -1);
}

void	clear_screen()
{
	int screen_size = MAX_COLS * MAX_ROWS;
	int i;
	char *screen = (char *)VIDEO_ADDRESS;

	i = -1;
	while (++i <= screen_size)
	{
		screen[i * 2] = ' ';
		screen[i * 2 + 1] = WHITE_ON_BLACK;
	}
	set_cursor(get_screen_offset(0, 0));
}

void	print_backspace()
{
	int	offset;
	int	row;
	int	col;

	offset = get_cursor() - 2;
	row = get_offset_row(offset);
	col = get_offset_col(offset);
	print_char(' ', col, row, WHITE_ON_BLACK);
	set_cursor(offset);
}
