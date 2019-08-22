#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>

void my_deal(int signum)
{
	int i = 0;
	while(i < 10)
	{
		printf("signum : %d\n",signum);
		sleep(1);
		i++;
	}
	return ;
}

int main(int argc, char *argv[])
{
    int i = 0;
//	signal(SIGALRM, sig);
	signal(SIGALRM, SIG_DFL);
	printf("alarm star\n");
	alarm(8); //默认3s后终止进程
	printf("alarm end\n");
	while(i < 12) //为了能等待进程能接受信号
	{
		i++;
		sleep(1);
		printf("%d\n",i);
	}
	printf("time is out!\n");
	return 0;
}
