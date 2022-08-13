#include "../drivers/screen.h"

void	main(void)
{
	clear_screen();
	//*((int*)0xb8000)=0x07690748;
	print("Hello World!\n");
}
