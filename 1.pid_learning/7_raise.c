#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
int main(int argc, char *argv[])
{
    pid_t pidt;
	pidt = fork();
	
	if(pidt > 0) //父进程的时候,pidt是子进程pid号
	{
		sleep(5);
		if(waitpid(pidt, NULL, WNOHANG) == 0) //等待子进程退出，不接受返回值，非阻塞。为0子进程没有退出
		//if(waitpid(pidt, NULL, 0) == 0)/*等待子进程退出，不接受返回值，阻塞。阻塞状态，不会执行下面程序*/
		{
			kill(pidt,9); //子进程被杀死，但没有回收资源，为僵尸进程
		}
		wait(NULL);//收集僵尸进程
		while(1);
	}
	
	if(pidt == 0)//子进程的时候，pidt就是fork的返回值0
	{
		printf("raise before\n");//要加\n才会进入到内核中，才可以进程通信;
		raise(SIGTSTP);//停止信号
		printf("died!\n");
		exit(0);
	}

	return 0;
}
