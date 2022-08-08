[org 0x7c00]

mov bx, my_string
call print
jmp end


my_string:
	db 'Hello World', 0


print:
	pusha

	start:
		mov al, [bx]
		cmp al, 0
		je done

		mov ah, 0x0e
		int 0x10

		add bx, 1
		jmp start

	done:
		popa
		ret


end:

jmp $
times 510-($-$$) db 0
dw 0xaa55
