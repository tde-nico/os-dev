#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include "kernel.h"

void	user_input(char *input)
{
	if (!strcmp(input, "exit"))
	{
		print("Stopping the CPU. Bye!\n");
		__asm__ __volatile__("hlt");
	}
	else if (!strcmp(input, "page"))
	{
		u32 phys_addr;
		u32 page = malloc(1000, 1, &phys_addr);
		char page_str[16] = "";
		hex_to_ascii(page, page_str);
		char phys_str[16] = "";
		hex_to_ascii(phys_addr, phys_str);
		print("Page: ");
		print(page_str);
		print(", physical address: ");
		print(phys_str);
		print("\n> ");
	}
	else
	{
		print("out: ");
		print(input);
		print("\n> ");
	}
}

void	kernel_main(void)
{
	clear_screen();
	isr_install();
	irq_install();
}
