AC = nasm
AFLAGS = -f bin
ENTRY_FLAGS = -f elf64
CC = gcc
CFLAGS = -ffreestanding
LINKER = ld
LFLAGS = -Ttext 0x1000 --oformat binary
EMU = qemu-system-x86_64
EFLAGS = -curses
IFLAGS = -drive format=raw,file=

RM = rm -rf

OBJ_DIR = objs

A_DIR = bootloader
ASM = $(A_DIR)/main.asm
BOOT = $(ASM:$(A_DIR)/%.asm=$(OBJ_DIR)/%.bin)

C_DIR = kernel
C_SRCS = $(wildcard $(C_DIR)/*.c)
OBJS = $(C_SRCS:$(C_DIR)/%.c=$(OBJ_DIR)/%.o)
ENTRY = $(C_DIR)/kernel_entry.asm
ENTRY_OBJ = $(ENTRY:$(C_DIR)/%.asm=$(OBJ_DIR)/%.o)
KERNEL = $(OBJ_DIR)/kernel.bin

IMAGE = os-image

all: $(IMAGE)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o : $(C_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o : $(C_DIR)/%.asm
	$(AC) $^ $(ENTRY_FLAGS) -o $@

$(BOOT): $(ASM) | $(OBJ_DIR)
	$(AC) $(AFLAGS) $< -o $@

$(KERNEL): $(ENTRY_OBJ) $(OBJS)
	echo $(ENTRY_OBJ)
	$(LINKER) -o $@ $(LFLAGS) $^

$(IMAGE): $(BOOT) $(KERNEL)
	cat $^ > $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(IMAGE)

re: fclean all

run: all
	$(EMU) $(EFLAGS) $(IFLAGS)$(IMAGE)


