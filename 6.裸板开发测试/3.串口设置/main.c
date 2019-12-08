#include "s3c2440_soc.h"
#include "uart.h"

int main(int argc, char const *argv[])
{
	unsigned char input = 0;
	uart0_init();
	puts("hellow lmafia\n");
	while(1)
	{
		input = getchar();
		putchar(input);
	}
	return 0;
}