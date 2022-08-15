#include "string.h"

int	strlen(char s[])
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	reverse_string(char s[])
{
	int	c;
	int	i;
	int	j;

	i = 0;
	j = strlen(s)-1;
	while (i < j)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
		i++;
		j--;
	}
}

void	int_to_ascii(int n, char str[]) {
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
	reverse_string(str);
}
