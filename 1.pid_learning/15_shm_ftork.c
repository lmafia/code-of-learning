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
	pid_t pid;
	key = ftok("a.c",'a');
	if(key < 0)
	{
	    perror(strerror(errno));	
		return -1;
	}
	shmid = shmget(key, 128, IPC_CREAT|0777);
	if(shmid < 0)
		return -1;
	
	parent_addr = (struct addr  *)shmat(shmid, NULL, 0);
    if(!parent_addr)
		return -1;
	signal(SIGUSR2, my_deal);
	
	parent_addr->pid = getpid();
	pause();
	pid = parent_addr->pid;
	printf("%d\n",pid);
	
	
	while(1)
	{
		printf("input:");
		scanf("%s",parent_addr->data);
		kill(pid,SIGUSR1);

	}
	
	shmdt(parent_addr);
	shmctl(shmid, IPC_RMID, NULL);
	return 0;
}