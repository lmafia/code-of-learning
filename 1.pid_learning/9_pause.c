#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
int main(int argc, char *argv[])
{
    int i = 0;
	printf("alarm star\n");
	alarm(3); //默认3s后终止进程
	printf("alarm end\n");
    pause();
	return 0;
}
