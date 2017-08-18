#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#define PORTNO 10275
int main()
{	
	int sockfd,newsockfd,portno,clilen,n=1;
	char buf[256];
	char* str = (char*) calloc(50,sizeof(char));
	struct sockaddr_in seraddr,cliaddr;
	int i,value;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
		perror("SocketError");
	seraddr.sin_family = AF_INET;
	seraddr.sin_addr.s_addr = INADDR_ANY;
	seraddr.sin_port = htons(PORTNO);
	int err = bind(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr));
	if(err == -1)	perror("Bind error");
	listen(sockfd,1);
	clilen = sizeof(clilen);
	while(1)
	{
		newsockfd=accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);
		if(newsockfd == -1) perror("New sock error");
		if(fork()==0)
		{
			n = read(newsockfd,buf,sizeof(buf));
			time_t rawtime;
			time(&rawtime);
			str =  asctime(localtime(&rawtime));
			n = write(newsockfd,str,40);
			int x = getpid();
						
			printf("%d\n",x);
			memset(buf,0,256);
			sprintf(buf,"%d\n",x);		
			n = write(newsockfd,buf,40);		
		}
	}	
	return 0;
}
