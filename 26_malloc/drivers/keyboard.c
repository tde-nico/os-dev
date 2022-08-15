#include "keyboard.h"
#include "../cpu/ports.h"
#include "screen.h"
#include "../cpu/isr.h"
#include "../libc/string.h"
#include "../libc/function.h"
#include "../kernel/kernel.h"

#define KEYBOARD_PIC_PORT 0x60
#define SC_MAX 0x39
#define BACKSPACE 0x0E
#define ENTER 0x1C
#define ASCII "??1234567890-=??qwertyuiop[]??asdfghjkl;\'\"?\\zxcvbnm,./??? "

static char	key_buffer[256];

static void	keyboard_callback(registers_t regs)
{
	u8		scancode;

	scancode = port_byte_in(KEYBOARD_PIC_PORT);
	if (scancode > SC_MAX)
		return ;
	if (scancode == BACKSPACE)
	{
		backspace(key_buffer);
		print_backspace();
	}
	else if (scancode == ENTER)
	{
		print("\n");
		user_input(key_buffer);
		key_buffer[0] = '\0';
	}
	else
	{
		char letter = ASCII[port_byte_in(KEYBOARD_PIC_PORT)];
		char str[2] = {letter, '\0'};
		append(key_buffer, letter);
		print(str);
	}
	UNUSED(regs);
}

void	init_keyboard()
{
	register_interrupt_handler(IRQ1, keyboard_callback);
}
