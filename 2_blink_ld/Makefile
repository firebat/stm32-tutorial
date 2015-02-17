PREFIX := arm-none-eabi-
.PHONY: all clean

all: main.bin

main.o: main.c
	$(PREFIX)gcc -mcpu=cortex-m3 -mthumb -nostartfiles -c main.c -o main.o

isr.o: isr.c
	$(PREFIX)gcc -mcpu=cortex-m3 -mthumb -nostartfiles -c isr.c -o isr.o

main.elf: main.o isr.o stm32f103c8.ld
	$(PREFIX)ld -T stm32f103c8.ld -o main.elf main.o isr.o

main.bin: main.elf
	$(PREFIX)objcopy -j .text -O binary main.elf main.bin

clean:
	rm -f *.o *.elf *.bin
