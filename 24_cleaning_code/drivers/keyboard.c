#include "keyboard.h"
#include "../cpu/ports.h"
#include "screen.h"
#include "../cpu/isr.h"
#include "../libc/string.h"
#include "../libc/function.h"

#define KEYBOARD_PIC_PORT 0x60
#define SC_MAX 0x39
#define BACKSPACE 0x0E
#define ENTER 0x1C
#define ASCII "??1234567890-=??qwertyuiop[]??asdfghjkl;\'\"?\\zxcvbnm,./??? "


static void	keyboard_callback(registers_t regs)
{
	u8		scancode;

	UNUSED(regs);
	scancode = port_byte_in(KEYBOARD_PIC_PORT);
	if (scancode > SC_MAX)
		return ;
	else if (scancode == ENTER)
		print("\n");
	else {
		char str[2] = {ASCII[port_byte_in(KEYBOARD_PIC_PORT)], '\0'};
		print(str);
	}
}

void	init_keyboard()
{
	register_interrupt_handler(IRQ1, keyboard_callback);
}
