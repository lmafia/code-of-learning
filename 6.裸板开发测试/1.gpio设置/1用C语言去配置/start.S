
.text
.global _start

_start:
	/*设置内存： sp栈指针*/
	ldr sp, =0x40000000+4096 /*NOR启动 NOR启动起始地址是0x40000000， 而4096是片内RAM的4k空间*/

	bl main /*bl回保存现场*/

halt_loop:
    b halt_loop
