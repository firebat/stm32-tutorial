CC 	  = arm-none-eabi-gcc
LD 	  = arm-none-eabi-ld
OBJCP = arm-none-eabi-objcopy

LD_SCRIPT = stm32f103c8.ld

CFLAGS  = -c -mcpu=cortex-m3 -mthumb
LDFLAGS  = -T $(LD_SCRIPT) -nostartfiles

all: main.bin

main.elf: main.o isr.o
	$(LD) $(LDFLAGS) -o main.elf main.o isr.o

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.bin: %.elf
	$(OBJCP) -O binary $< $@

clean:
	rm -f *.o *.elf *.bin

.PHONY: all clean
