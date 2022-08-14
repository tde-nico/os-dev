#include "../drivers/screen.h"
#include "util.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"


void	main(void)
{
	clear_screen();
	isr_install();
	__asm__ __volatile__("sti");
	init_timer(50);
	init_keyboard();
}
