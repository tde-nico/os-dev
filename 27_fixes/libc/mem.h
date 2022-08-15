#ifndef MEM_H
#define MEM_H

#include "../cpu/types.h"

void	memory_copy(char *source, char *dest, int no_bytes);
u32		malloc(u32 size, int align, u32 *phys_addr);

#endif
