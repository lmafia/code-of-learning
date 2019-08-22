
#include "s3c2440_soc.h"
#include "uart.h"
#include "my_printf.h"
#include "init.h"
int main(void)
{
	unsigned char c;
	
	uart0_init();
	puts("Hello, world!\n\r");
	my_printf_test();
	while(1)
	{
		c = getchar(); /*getchar 输入int的*/
		if (c == '\r')
		{
			putchar('\n');
		}
		putchar(c);
		if(c >= '0' && c <= '7')
		{
		    bank0_tacc_set(c - '0');
		    led_test();
		}

	}
	return 0;
}



