AC = nasm
AFLAGS = -f bin
RM = rm -rf
EMU = qemu-system-x86_64
EFLAGS = -curses

SRCS = main.asm
OUT = $(SRCS:%.asm=%.bin)

$(OUT): $(SRCS)
	$(AC) $(AFLAGS) $(SRCS) -o $(OUT)

all: $(OUT)

clean:
	$(RM) $(OUT)

re: clean all

run: all
	$(EMU) $(EFLAGS) $(OUT)

