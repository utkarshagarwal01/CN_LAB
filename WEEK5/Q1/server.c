#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <time.h>
#define PORTNO 9740
int main()
{
	int server_sockfd,client_sockfd,server_len,client_len;
	struct sockaddr_in server_address,client_address;
	int result;fd_set writefds,testfds,readfds;
	char* str = (char*) calloc(50,sizeof(char));
	server_sockfd = socket(AF_INET,SOCK_STREAM,0);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(PORTNO);
	server_len = sizeof(server_address);
	bind(server_sockfd,(struct sockaddr*)&server_address,server_len);
	listen(server_sockfd,5);
	FD_ZERO(&writefds);
	FD_ZERO(&readfds);		
	FD_SET(server_sockfd,&readfds);
	printf("Server Sockfd: %d\n",server_sockfd);
	while(1)
	{
		char ch;int fd,nread;
		testfds = writefds;
		
		printf("Server Waiting\n");
		result = select(FD_SETSIZE,&readfds,&writefds,(fd_set *)0,(struct timeval *)0);
		printf("Number of write fds:%d\n",result);
		if(result <1)
		{
			perror("Server Error\n");
			exit(1);
		}
		for(fd = 0 ; fd<FD_SETSIZE;fd++)
		{
			if(FD_ISSET(fd,&readfds))
			{
				if(fd == server_sockfd)
				{
					client_len = sizeof(client_address);
					client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address,&client_len);
					FD_SET(client_sockfd,&writefds);
					printf("Adding client on fd %d\n",client_sockfd);
				}
			}
			if(FD_ISSET(fd,&writefds))
			{
				sleep(5);
				printf("Serving client on fd %d\n",fd);
				time_t rawtime;
				time(&rawtime);
				str =  asctime(localtime(&rawtime));
				write(fd,str,50);	

				close(fd);
				FD_CLR(fd,&writefds);
				printf("Removing client on fd %d\n",fd);
			}
		}
	}
}

					
