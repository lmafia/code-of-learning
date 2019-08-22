#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <errno.h>
struct msgbuf
{
	long mtype;
	char mtex[124];
	char msgid[4];
};

int main ()
{
	int msgid, recv_num,key;
	pid_t pid;
	struct msgbuf sendbuf, recvbuf;
	key = ftok("a.c", 'a');
	msgid = msgget(key, IPC_CREAT|0777);
	if(msgid < 0)
		return -1;
	printf("msgid = %d\n", msgid);  
	system("ipcs -q");
	pid = fork();
	if(pid < 0)
		return -1;
    if(pid > 0)
	{
		while(1)
		{
			memset(recvbuf.mtex, 0, 124);
			msgrcv(msgid, (void *)&recvbuf, 124, 1, 0); //设置为阻塞方式，不需要pause去阻塞
			printf("message :%s\n",recvbuf.mtex);
		}
	}
    if(pid == 0)
	{			
	    sendbuf.mtype = 2;
		while(1)
		{
			memset(sendbuf.mtex, 0, 124);
			printf("input:");
			scanf("%s",sendbuf.mtex);
			msgsnd(msgid, (void *)&sendbuf, strlen(sendbuf.mtex), 0);
		}
	}		

	msgctl(msgid, IPC_RMID, NULL);
	system("ipcs -q");
	return 0;
}