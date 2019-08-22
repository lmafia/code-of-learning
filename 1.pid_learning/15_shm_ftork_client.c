#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <errno.h>

struct addr 
{
    pid_t pid;
    char data[124];	
};
void my_deal(int signum)
{
    return;
}

int main ()
{
	int key, shmid;
	struct addr  *parent_addr;
	pid_t pid = 0;
	key = ftok("a.c",'a');
	if(key < 0)
	{
	    perror(strerror(errno));	
		return -1;
	}
	shmid = shmget(key, 128, IPC_CREAT|0777);
	if(shmid < 0)
	{
	    perror(strerror(errno));	
		return -1;
	}
	parent_addr = (struct addr  *)shmat(shmid, NULL, 0);
    if(!parent_addr)
	{
	    perror(strerror(errno));	
		return -1;
	}
	signal(SIGUSR1, my_deal);
	
	pid = parent_addr->pid;
	printf("%d\n",pid);
	if(!pid)
	{
	    perror(strerror(errno));	
		return -1;
	}
	parent_addr->pid = getpid();
	kill(pid,SIGUSR2);
	
	while(1)
	{
		pause();
		printf("output: %s\n", parent_addr->data);
		kill(pid,SIGUSR2);
	}
	
	shmdt(parent_addr);
	shmctl(shmid, IPC_RMID, NULL);
	return 0;
}