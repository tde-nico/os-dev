print_hex:
	pusha
	mov cx, 4

	hex_loop:
		dec cx

		mov ax, dx
		shr dx, 4
		and ax, 0xf

		mov bx, HEX_OUT
		add bx, 2
		add bx, cx

		cmp ax, 0xa
		jl set_letter

		add al, 0x27
		jl set_letter
	
	set_letter:
		
		add al, 0x30
		mov byte [bx], al

		cmp cx, 0
		je end
		jmp hex_loop

	end:
		mov bx, HEX_OUT
		call print

		popa
		ret

HEX_OUT:
	db '0x0000', 0

%include "print.asm"
