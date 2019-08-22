#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

void my_deal(int signum)
{

	for(int i = 0; i < 10; i++)
	{
		sleep(1);
		printf("get the signal %d %d\n",signum,i);
	}		
}
void my_rec(int signum)
{
	printf("get the signal %d\n",signum);
	wait(NULL);
}
int main(int argc, char *argv[])
{
    pid_t pidt;
	pidt = fork();
	
	if(pidt > 0) //父进程的时候,pidt是子进程pid号
	{
		signal(SIGUSR1, my_deal);
		signal(SIGCHLD, my_rec);
		for(int i = 0; i < 10; i++)
			sleep(1);
	}
	
	if(pidt == 0)//子进程的时候，pidt就是fork的返回值0
	{
		printf("raise before\n");//要加\n才会进入到内核中，才可以进程通信;
		kill(getppid(), SIGUSR1);
		printf("died!\n");
		exit(0); //已经死了，变僵尸，等父进程来回收
	}

	return 0;
}
