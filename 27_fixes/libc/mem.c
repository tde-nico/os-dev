#include "mem.h"

static u32	free_mem_addr = 0x10000;

void	memory_copy(char *source, char *dest, int no_bytes)
{
	int	i;

	i = -1;
	while (++i < no_bytes)
		*(dest + i) = *(source + i);
}

u32	malloc(u32 size, int align, u32 *phys_addr)
{
	if (align == 1 && (free_mem_addr & 0xFFFFF000))
	{
		free_mem_addr &= 0xFFFFF000;
		free_mem_addr += 0x1000;
	}
	if (phys_addr)
		*phys_addr = free_mem_addr;
	u32 ret = free_mem_addr;
	free_mem_addr += size;
	return ret;
}
