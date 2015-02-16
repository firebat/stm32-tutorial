PREFIX := arm-none-eabi-
.PHONY: all clean

all: main.bin

main.o: main.c
	$(PREFIX)gcc -mcpu=cortex-m3 -mthumb -nostartfiles -c main.c -o main.o

main.elf: main.o simple.ld
	$(PREFIX)ld -T simple.ld -o main.elf main.o

main.bin: main.elf
	$(PREFIX)objcopy -j .text -O binary main.elf main.bin

clean:
	rm -f *.o *.elf *.bin
