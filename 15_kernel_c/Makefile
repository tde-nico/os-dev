AC = nasm
AFLAGS = -f bin
CC = gcc
CFLAGS = -ffreestanding
LINKER = ld
LFLAGS = -Ttext 0x1000 --oformat binary
EMU = qemu-system-x86_64
EFLAGS = -curses
IFLAGS = -drive format=raw,file=

RM = rm -rf

ASM = main.asm
BOOT = $(ASM:%.asm=%.bin)

SRC = kernel.c
OBJ = $(SRC:%.c=%.o)
KERNEL = $(SRC:%.c=%.bin)

IMAGE = os-image

all: $(IMAGE)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BOOT): $(ASM)
	$(AC) $(AFLAGS) $< -o $@

$(KERNEL): $(OBJ)
	$(LINKER) -o $@ $(LFLAGS) $<

$(IMAGE): $(BOOT) $(KERNEL)
	cat $< > $@

clean:
	$(RM) $(BOOT)
	$(RM) $(OBJ)
	$(RM) $(KERNEL)

fclean: clean
	$(RM) $(IMAGE)

re: fclean all

run: all
	$(EMU) $(EFLAGS) $(IFLAGS)$(IMAGE)


