
.text
.global _start

_start:

	/**
	 * FCLK : HCLK : PCLK = 400 : 100 : 50
	 * LOCKTIME(0x40000000) = 0xFFFFFFFF
	 *  CLKDIVN(0x4C000014) = 0x5 TFCLK:THCLK:TPCLK = 1:4:8
	 * 
	 */
	ldr r0, =0x4C000000
	ldr r1, =0xFFFFFFFF
	str r1, [r0]

	ldr r0, =0x4C000014
	ldr r1, =0x5
	str r1, [r0]
	/*
	 * 当HDVIN 不为0时要使用FCLK
	 * 要设置CPU为异步模式
	 */
	mrc p15,0,r0,c1,c0,0
	orr r0,r0, #0xC0000000
	mcr p15,0,r0,c1,c0,0
	/**
	 * 设置MPLLCON(0x4C000004) = (92<<12) | (1<<4) | (1<<0) 
	 * 一设置PLL就会锁定LOCKTIME直到PLL输出稳定，CPU有默认时钟频率转为新的时钟频率
	 */
	ldr r0, =0x4C000004
	ldr r1, =(92<<12) | (1<<4) | (1<<0) 
	str r1, [r0]

	/*关闭看门狗*/
	ldr r0, =0x53000000
	mov r1, #0
	str r1, [r0]
	/* 设置内存： sp栈指针*/
    /* 
     * 自动辨别nor/nand启动
     *
     */
    mov r1, #0
    ldr r0, [r1]
    str r1, [r1]
    ldr r2, [r1]
    cmp r1, r2 /*相等为nand启动*/
    ldr sp, =0x40000000+4096 /*NOR启动 NOR启动起始地址是0x40000000， 而4096是片内RAM的4k空间*/
    moveq sp, #4096
    streq r0, [r1]




	bl main /*bl回保存现场*/

halt_loop:
    b halt_loop
