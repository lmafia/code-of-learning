#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>

void my_deal(int signum)
{
    return;
}

int main ()
{
	int shmid;
	char *parent_addr;
	char *child_addr;
	pid_t pid;
	shmid = shmget(IPC_PRIVATE, 128, IPC_CREAT|0777);
	if(shmid < 0)
		return -1;
	pid = fork();
	if(pid > 0)
	{
		parent_addr = (char *)shmat(shmid, NULL, 0);
		if(!parent_addr)
			return -1;
		signal(SIGUSR2,my_deal); //因为SIGUSR,动作默认是终止进程
		while(1)
		{
			printf("intput:");
			scanf("%s",parent_addr); //写入内存
			kill(pid, SIGUSR1); //告诉子进程
			
			pause(); //睡眠等待
		}
	}
		
	if(pid == 0)
	{
		child_addr = (char *)shmat(shmid, NULL, 0);
		if(!child_addr)
			return -1;
		signal(SIGUSR1, my_deal);
		while(1)
		{
			pause(); //睡眠等待
			printf("reception:");
			printf("1%s\n",child_addr); //读出内容
			printf("2%s\n",child_addr);
			printf("3%s\n",child_addr); //一直存在共享内存中，123都是一样的内容
			kill(getppid(), SIGUSR2); //读取完毕，告诉父进程
		}
	}
	shmdt(parent_addr);
	shmdt(child_addr);
	shmctl(shmid, IPC_RMID, NULL);
	return 0;
}