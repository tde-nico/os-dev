mov ah, 0x0e

mov bx, 4
;mov bx, 5

cmp bx, 4
je if
jmp else
jmp endif

if:
	mov al, '1'
	jmp endif

else:
	mov al, '2'
	jmp endif

endif:
int 0x10

jmp $
times 510-($-$$) db 0
dw 0xaa55
