
.text
.global _start

_start:
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
