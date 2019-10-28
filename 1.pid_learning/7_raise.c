/**
* 信号通信
* 信号是内核已经存在的，是内核自带的玩意儿，在shell用kill -l可查看，一共64种
* 所以 kill 9 pid号 就是发送终止信号给进程，并终止进程
* 信号发送：
*			kill() --- int kill(pid_t pid, int signal)
*                 
*			raise() --- int raise(int signl) 自己发给自己信号
*
*			alarm() --- unsigned int alarm( unsigned int seconds) 定时xx秒后发送闹钟信号给自己，较前2者，前2者是立即的，
*																  而这个是延时的、
* 
* 信号接收：应该是内核会让进程自动接收，不过这时候需要进程一直等待or睡眠
*			pause() 一直睡眠
*			sleep() 定时睡眠
*			while(1) 死循环
* 信号处理：
*			signal() --- void *signal(int sig, void(*handler)(int))(int) 自定义信号处理函数，默认的处理是根据不同信号会有不同的默认处理函数的
*
*			sigaction() --- int sigaction (int sig, const struct sigaction *act, struct sigaction *oact) 这个比signal更强大
**/


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
