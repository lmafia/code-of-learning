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
	int msgid, recv_num;
	struct msgbuf sendbuf, recvbuf;
	system("ipcs -q");
	msgid = msgget(IPC_PRIVATE, 0777);
	if(msgid < 0)
		return -1;
	sendbuf.mtype = 1;
	printf("msgid = %d\n", msgid);
	printf("input:\n");
	scanf("%s", sendbuf.mtex);
	msgsnd(msgid, (void *)&sendbuf, strlen(sendbuf.mtex), 0);
	system("ipcs -q");
	
	sendbuf.mtype = 2;
	printf("input:\n");
	scanf("%s", sendbuf.mtex);
	msgsnd(msgid, (void *)&sendbuf, strlen(sendbuf.mtex), 0);
	
	memset(recvbuf.mtex, 0, 124);
	recv_num = msgrcv(msgid, (void *)&recvbuf, 2, 2, 0);
	printf("the length:%d\n", recv_num);
	
	printf("message : %s\n",recvbuf.mtex);
	system("ipcs -q");
	msgctl(msgid, IPC_RMID, NULL);
	return 0;
}