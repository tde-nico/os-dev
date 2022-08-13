void	memory_copy(char *source, char *dest, int no_bytes)
{
	int	i;

	i = -1;
	while (++i < no_bytes)
		*(dest + i) = *(source + i);
}
