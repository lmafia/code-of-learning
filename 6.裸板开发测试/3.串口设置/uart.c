#include "s3c2440_soc.h"


void uart0_init()
{
	GPHCON &= ~( (3<<4) | (3<<6) );
	GPHCON |= ( (2<<4) | (2<<6) );
	GPHUP &= ~( (1<<2) | (1<<3) );

	UCON0 = 0x5;
	UBRDIV0 = 26;  // 
	ULCON0 = 0x3; // 8n1

}

int putchar( int c)
{
	//UTRSTAT0
	// UTXH0
	while(!(UTRSTAT0 & (1<<2)));
	UTXH0 = (unsigned char)c;
	return 0;
}

int getchar()
{
	// URXH0
	while(!(UTRSTAT0 & (1<<0)));
	return (URXH0);
}

int puts(const char *str)
{
	if(str == 0 || *str == '\0')
		return -1;
	while(*str != '\0')
	{
		putchar(*str);
		str++;
	}
	return 0;
}
