[bits 16]

switch_to_pm:
	mov ax, 0x2401
	int 0x15
	mov ax, 0x3
	int 0x10

	cli
	lgdt [gdt_descriptor]

	mov eax, cr0
	or eax, 0x1
	mov cr0, eax

	jmp CODE_SEG:init_pm

[bits 32]

init_pm:
	mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ebp, 0x90000
	mov esp, ebp

	call BEGIN_PM
