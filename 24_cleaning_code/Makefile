AC = nasm
AFLAGS = -f bin
ENTRY_FLAGS = -f elf
CC = gcc
CFLAGS =	-ffreestanding \
			-m32 \
			-z execstack \
			-fno-stack-protector \
			-fno-builtin \
			-fno-pic \
			-no-pie \
			-nostdlib \
			-nostdinc \
			-nostartfiles \
			-nodefaultlibs \
			-Wall \
			-Wextra \
			-Werror \
			-g

			
LINKER = ld
LFLAGS = -Ttext 0x1000 --oformat binary -m elf_i386 -s
EMU = qemu-system-x86_64
EFLAGS = -curses
IFLAGS = -drive format=raw,file=

RM = rm -rf

OBJ_DIR = objs

B_DIR = boot
ASM = $(B_DIR)/main.asm
BOOT = $(ASM:$(B_DIR)/%.asm=$(OBJ_DIR)/%.bin)

K_DIR = kernel
D_DIR = drivers
C_DIR = cpu
L_DIR = libc
K_SRCS = $(wildcard $(K_DIR)/*.c)
D_SRCS = $(wildcard $(D_DIR)/*.c)
C_SRCS = $(wildcard $(C_DIR)/*.c)
L_SRCS = $(wildcard $(L_DIR)/*.c)

OBJS =	$(K_SRCS:$(K_DIR)/%.c=$(OBJ_DIR)/%.o) \
		$(D_SRCS:$(D_DIR)/%.c=$(OBJ_DIR)/%.o) \
		$(C_SRCS:$(C_DIR)/%.c=$(OBJ_DIR)/%.o) \
		$(L_SRCS:$(L_DIR)/%.c=$(OBJ_DIR)/%.o)

ENTRY = $(K_DIR)/kernel_entry.asm
INTERRUPT = $(C_DIR)/interrupt.asm
ENTRY_OBJ = $(ENTRY:$(K_DIR)/%.asm=$(OBJ_DIR)/%.o)
INTERRUPT_OBJ = $(INTERRUPT:$(C_DIR)/%.asm=$(OBJ_DIR)/%.o)

KERNEL = $(OBJ_DIR)/kernel.bin

IMAGE = os-image

all: $(IMAGE)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o : $(K_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o : $(D_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o : $(C_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o : $(L_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o : $(K_DIR)/%.asm
	$(AC) $^ $(ENTRY_FLAGS) -o $@
$(OBJ_DIR)/%.o : $(C_DIR)/%.asm
	$(AC) $^ $(ENTRY_FLAGS) -o $@

$(BOOT): $(ASM) | $(OBJ_DIR)
	$(AC) $(AFLAGS) $< -o $@

$(KERNEL): $(ENTRY_OBJ) $(INTERRUPT_OBJ) $(OBJS)
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


