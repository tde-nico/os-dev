#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../libc/string.h"
#include "kernel.h"

void	user_input(char *input)
{
	if (!strcmp(input, "exit"))
	{
		print("Stopping the CPU. Bye!\n");
		__asm__ __volatile__("hlt");
	}
	print("out: ");
	print(input);
	print("\n> ");
}

void	main(void)
{
	clear_screen();
	isr_install();
	irq_install();
}
