#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
	
	int  sockfd;
	struct sockaddr_in servaddr;
	int bytes;
	char buf[100];
	if((sockfd = socket(AF_INET, SOCK_STREAM,0)) < 0)
	{
		perror("error\n");
		return -1;
	}
	bzero(&servaddr, sizeof(struct sockaddr_in));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(8888);
	
	if( connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("error\n");
		return -1;
	}
    bytes = read(sockfd, buf, 100);
	if(bytes < 0)
	{
		perror("read fail\n");
		return -1;
	}
	if(bytes == 0)
	{
		perror("close connection\n");
		return -1;
	}
	printf("read bytes : %d\n", bytes);
	printf("time:%s\n",buf);
	close(sockfd);
		
}
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 