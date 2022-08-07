AC = nasm
AFLAGS = -f bin
RM = rm -rf
EMU = qemu-system-x86_64
EFLAGS = --nographic

SRCS = $(wildcard *.asm)
OUT = $(SRCS:%.asm=%.bin)

$(OUT):
	$(AC) $(AFLAGS) $(SRCS) -o $(OUT)

all: $(OUT)

clean:
	$(RM) $(OUT)

re: clean all

run: all
	$(EMU) $(EFLAGS) $(OUT)

