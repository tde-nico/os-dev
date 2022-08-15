#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"


void	main(void)
{
	clear_screen();
	isr_install();
	irq_install();
}
