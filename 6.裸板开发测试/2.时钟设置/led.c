

void delay(volatile x)
{
	while(x--);
}

int  main()
{
	unsigned int *pGPFCON = (unsigned int *)0x56000050;
	unsigned int *pGPFDAT = (unsigned int *)0x56000054;
	*pGPFCON &= ~((3<<8) | (3<<10) | (3<<12)) ; /*清零*/
	*pGPFCON |=  ((1<<8) | (1<<10) | (1<<12)) ; /*设置*/
	unsigned int val = 0;
	while(1)
	{
		*pGPFDAT &= ~(7<<4);
		*pGPFDAT |= (val<<4);
		delay(10000);
		val++;
		if(val == 8)
			val = 0;
	}

	return 0;
}
