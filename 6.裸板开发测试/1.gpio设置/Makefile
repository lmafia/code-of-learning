all:
	arm-linux-gcc -c led1.S -o led1.o
	arm-linux-ld -Ttext 0 led1.o -o led1.elf
	arm-linux-objcopy -O binary -S led1.elf led1.bin
	arm-linux-objdump -D led1.elf > led1.dis
clean:
	rm *.bin *.elf *.o
