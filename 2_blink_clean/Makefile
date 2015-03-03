CC    = arm-none-eabi-gcc
LD    = arm-none-eabi-ld
OBJCP = arm-none-eabi-objcopy

SOURCES = $(wildcard *.c)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

LD_SCRIPT = stm32f103c8.ld

CFLAGS  = -c -mcpu=cortex-m3 -mthumb
LDFLAGS = -T $(LD_SCRIPT) -nostartfiles

all: main.bin

main.elf: $(OBJECTS)
	$(LD) $(LDFLAGS) -o main.elf $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.bin: %.elf
	$(OBJCP) -O binary $< $@

clean:
	rm -f *.o *.elf *.bin

.PHONY: all clean
