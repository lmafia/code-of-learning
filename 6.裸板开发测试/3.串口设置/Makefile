all:
	arm-linux-gcc -c uart.c -o uart.o
	arm-linux-gcc -c start.S -o start.o
	arm-linux-gcc -c main.c -o main.o
	arm-linux-ld -Ttext 0 start.o uart.o main.o -o uart.elf
	arm-linux-objcopy -O binary -S uart.elf uart.bin
	arm-linux-objdump -D uart.elf > uart.dis


clean:
	rm *.bin *.o *elf *.dis