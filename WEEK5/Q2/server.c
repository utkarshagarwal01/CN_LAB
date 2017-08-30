#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> 
#define PORTNO 9741
int main()
{
	int server_sockfd,client_sockfd,server_len,client_len;
	struct sockaddr_in server_address,client_address;
	int result;fd_set readfds,testfds;
	server_sockfd = socket(AF_INET,SOCK_STREAM,0);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(PORTNO);
	server_len = sizeof(server_address);
	bind(server_sockfd,(struct sockaddr*)&server_address,server_len);
	listen(server_sockfd,5);
	FD_ZERO(&readfds);
	FD_SET(server_sockfd,&readfds);
	printf("Server Sockfd: %d\n",server_sockfd);
	char ch[256],buf[256];memset(ch,0,256);memset(buf,0,256);
	while(1)
	{
		int fd,nread;
		testfds = readfds;
		printf("Server Waiting\n");
		result = select(FD_SETSIZE,&testfds,(fd_set *)0,(fd_set *)0,(struct timeval *)0);
		printf("%d Read fd's are open.\n",result);
		if(result <1)
		{
			perror("Server Error\n");
			exit(1);
		}
		for(fd = 0 ; fd<FD_SETSIZE;fd++)
		{
			if(FD_ISSET(fd,&testfds))
			{
				if(fd == server_sockfd)
				{
					client_len = sizeof(client_address);
					client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address,&client_len);
					FD_SET(client_sockfd,&readfds);
					printf("Adding client on fd %d\n",client_sockfd);
				}
				else
				{
					ioctl(fd,FIONREAD,&nread);
					if(nread ==0)
					{
						close(fd);
						FD_CLR(fd,&readfds);
						printf("Removing client on fd %d\n",fd);
					}
					else
					{
						read(fd,ch,sizeof(ch));
						sleep(5);
						printf("Serving client on fd %d\n",fd);
						int i = 0;
						while(ch[i]!='\0')
						{
							if(ch[i]>96 && ch[i]<123)
								buf[i] = ch[i] - 32;
							else
								buf[i] = ch[i];
							i++;						
						}						
						write(fd,buf,sizeof(buf));
					}
				}
			}
		}
	}
}

					
