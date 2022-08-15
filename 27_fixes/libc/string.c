#include "string.h"
#include "../cpu/types.h"

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

int	strcmp(char s1[], char s2[])
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i++] == '\0')
			return (0);
	}
	return (s1[i] - s2[i]);
}

void	append(char s[], char n)
{
	int len;
	
	len = strlen(s);
	s[len] = n;
	s[len + 1] = '\0';
}

void	backspace(char s[])
{
	int len;
	
	len = strlen(s);
	s[len - 1] = '\0';
}

void	hex_to_ascii(int n, char str[])
{
	char	zeros;
	s32		tmp;
	int		i;
	
	zeros = 0;
	i = 32;
	append(str, '0');
	append(str, 'x');
	while (i > 0)
	{
		i -= 4;
		tmp = (n >> i) & 0xF;
		if (tmp == 0 && zeros == 0)
			continue;
		zeros = 1;
		if (tmp > 0xA)
			append(str, tmp - 0xA + 'a');
		else
			append(str, tmp + '0');
	}
	tmp = n & 0xF;
	if (tmp >= 0xA)
		append(str, tmp - 0xA + 'a');
	else
		append(str, tmp + '0');
}
