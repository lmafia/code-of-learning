#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
void *pthread_func(void *arg)
{
	int state_val, type_val;
	state_val = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	if(state_val)
	    printf("set cancel state fail\n");
    printf("this is new thread\n");
	sleep(4);
	
	printf("cancel ...\n");
	pthread_cancel(pthread_self());/*自己取消自己*/
	state_val = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	if(state_val)
		printf("set cancel state failed\n");
	//pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	/*test cancellation piont*/
	printf("the first point\n");
	printf("thr second point\n");
	
	return (void *)20;
}

int main()
{
	pthread_t tid;
	int create_ret, cancel_ret, join_ret;
	void * rval;
	
	create_ret = pthread_create(&tid, NULL, pthread_func, NULL);
	if(create_ret)
	{
		printf("create pthread failed\n");
		return -1;
	}
	
	//cancel_ret = pthread_cancel(tid);
	if(cancel_ret)
		printf("cancel pthread failed\n");

    join_ret = pthread_join(tid, &rval);
	
	printf("the pthread exit code:%d\n", (int *)rval);
	return 0;
}