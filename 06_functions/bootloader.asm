mov ah, 0x0e

call print
jmp end

print:
	pusha
	mov al, '1'
	int 0x10
	popa
	ret

end:

jmp $
times 510-($-$$) db 0
dw 0xaa55
