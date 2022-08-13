AC = nasm
AFLAGS = -f bin
ENTRY_FLAGS = -f elf
CC = gcc
CFLAGS = -ffreestanding -fno-stack-protector -z execstack -m32 -no-pie -fno-pic
LINKER = ld
LFLAGS = -Ttext 0x1000 --oformat binary -m elf_i386 -s
EMU = qemu-system-x86_64
EFLAGS = -curses
IFLAGS = -drive format=raw,file=

RM = rm -rf

OBJ_DIR = objs

A_DIR = boot
ASM = $(A_DIR)/main.asm
BOOT = $(ASM:$(A_DIR)/%.asm=$(OBJ_DIR)/%.bin)

K_DIR = kernel
D_DIR = drivers
ENTRY = $(K_DIR)/kernel_entry.asm
K_SRCS = $(wildcard $(K_DIR)/*.c)
D_SRCS = $(wildcard $(D_DIR)/*.c)

HEADERS = $(wildcard $(D_DIR)/*.h)

OBJS = $(K_SRCS:$(K_DIR)/%.c=$(OBJ_DIR)/%.o) $(D_SRCS:$(D_DIR)/%.c=$(OBJ_DIR)/%.o)
ENTRY_OBJ = $(ENTRY:$(K_DIR)/%.asm=$(OBJ_DIR)/%.o)
KERNEL = $(OBJ_DIR)/kernel.bin

IMAGE = os-image

all: $(IMAGE)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o : $(K_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o : $(D_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o : $(K_DIR)/%.asm
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


