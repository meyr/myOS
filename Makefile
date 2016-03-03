TCDIR = /usr/local/gcc-arm-2015q3
PREFIX = $(TCDIR)/bin/arm-none-eabi-

GCC     = $(PREFIX)gcc
OBJCOPY = $(PREFIX)objcopy
OBJDUMP = $(PREFIX)objdump
SIZE    = $(PREFIX)size
GDB     = $(PREFIX)gdb

#CFLAG += -v
CFLAG += -Wall -g -ggdb
CFLAG += -mcpu=cortex-m3 -mlittle-endian -mthumb
CFLAG += -nostartfiles -nostdlib -fno-builtin
CFLAG += -fomit-frame-pointer
CFLAG += -Iinc/
CFLAG += -Tmyos.ld

SRCS  = $(shell ls src/*.c) $(shell ls src/*.s)
OBJS1 = $(SRCS:.c=.o)
OBJS  = $(OBJS1:.s=.o)

test:
	@echo SRCS = $(SRCS)
	@echo OBJS = $(OBJS)
%.o: %.s
	$(GCC) $(CFLAG) -c $< -o $@
%.o: %.c
	$(GCC) $(CFLAG) -c $< -o $@

main: $(OBJS)
	$(GCC) $(CFLAG) $^ -o main.elf
	$(SIZE) main.elf
	$(OBJCOPY) -O binary main.elf main.bin
	$(OBJDUMP) -S main.elf > main.list
.PHONY: clean
clean:
	rm -rf $(OBJS) main.elf main.bin main.list

.PHONY: write
write: main.bin
	st-flash --reset write $< 0x8000000
listen:
	st-util
debug: main.elf
	$(GDB) $< -q -ex "target extended localhost:4242"
