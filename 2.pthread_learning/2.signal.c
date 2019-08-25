#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
void sig_handler1(int sig)
{
	printf("thread 1 get\n");
	sleep(3);
	printf("thread 1 get\n");
	return;
}
void sig_handler2(int sig)
{
	printf("thread 2 get\n");
	return;
}

void *thread_func1(void *arg)
{
	printf("the new threa 1\n");
	
	struct sigaction act;
	memset(&act, 0, sizeof(struct sigaction));
	sigaddset(&act.sa_mask, SIGINT);
	sigaddset(&act.sa_mask, SIGSTOP);
	act.sa_handler = sig_handler1;
	sigaction(SIGQUIT, &act, NULL);
	//pthread_sigmask(SIG_BLOCK, &act.sa_mask, NULL);
    while(1);
	return (void *)0;
}

void *thread_func2(void *arg)
{
	printf("the new threa 2\n");
	
	struct sigaction act;
	memset(&act, 0, sizeof(struct sigaction));
	sigaddset(&act.sa_mask, SIGQUIT);
	act.sa_handler = sig_handler2;
	sigaction(SIGQUIT, &act, NULL); /*全部进程的线程只会对应一个信号处理函数，如果*/
	pthread_sigmask(SIG_BLOCK, &act.sa_mask, NULL);
	sleep(2);
	return (void *)0;
}

int main()
{
	pthread_t tid1, tid2;
    if(pthread_create(&tid1, NULL, thread_func1, NULL))
	{
	     printf("create failed\n");
		 return -1;
	}

    // if(pthread_create(&tid2, NULL, thread_func2, NULL))
	// {
	     // printf("create failed\n");
		 // return -1;
	// }
	
	sleep(2);
	

	if(pthread_kill(tid1, SIGQUIT))
	{
		printf("send failed\n");
	}
	usleep(2);
		if(pthread_kill(tid1, SIGSTOP))
	{
		printf("send failed\n");
	}
		// if(pthread_kill(tid2, SIGQUIT))
	// {
		// printf("send failed\n");
	// }
	pthread_join(tid1, NULL);
	//pthread_join(tid2, NULL);
	return 0;
}