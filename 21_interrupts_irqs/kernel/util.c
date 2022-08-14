#include "util.h"

void	memory_copy(char *source, char *dest, int no_bytes)
{
	int	i;

	i = -1;
	while (++i < no_bytes)
		*(dest + i) = *(source + i);
}

void int_to_ascii(int n, char str[]) {
	int i;
	int	sign;

	sign = n;
	if (n < 0)
		n = -n;
	i = 0;
	while (n > 0)
	{
		str[i++] = n % 10 + '0';
		n /= 10;
	}
	if (sign < 0)
		str[i++] = '-';
	str[i] = '\0';
}
