#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<time.h>
#define PORTNO 10223
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
	bind(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr));
	listen(sockfd,1);
	clilen = sizeof(clilen);
	newsockfd=accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);
	n = read(newsockfd,buf,sizeof(buf));
	time_t rawtime;
	time(&rawtime);
	str =  asctime(localtime(&rawtime));
	n = write(newsockfd,str,50);		
	return 0;
}
