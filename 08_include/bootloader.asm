[org 0x7c00]

mov bx, my_string
call print


jmp $


%include "print.asm"

my_string:
	db 'Hello World', 0


times 510-($-$$) db 0
dw 0xaa55
