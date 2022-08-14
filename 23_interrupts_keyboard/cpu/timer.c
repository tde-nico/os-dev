#include "timer.h"
#include "../drivers/screen.h"
#include "../drivers/ports.h"
#include "../kernel/util.h"
#include "isr.h"

u32	tick = 0;

static void	timer_callback(registers_t regs)
{
	char	tick_ascii[256];

	tick++;
	/*print("Tick: ");
	int_to_ascii(tick, tick_ascii);
	print(tick_ascii);
	print("\n");*/
}

void	init_timer(u32 freq)
{
	u32	divisor;
	u8	low;
	u8	high;

	register_interrupt_handler(IRQ0, timer_callback);
	divisor = 1193180 / freq;
	low = (u8)(divisor & 0xFF);
	high = (u8)((divisor >> 8) & 0xFF);
	port_byte_out(0x43, 0x36);
	port_byte_out(0x40, low);
	port_byte_out(0x40, high);
}
