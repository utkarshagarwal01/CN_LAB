#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <error.h>
#include <time.h>
#include <stdlib.h>
#define PORTNO 10351
int main()
{
  	int sockfd,newsockfd,portno,status,clien,n=1;
 	char ch[265],buf[256];
 	struct sockaddr_in seraddr,cliaddr;
 	int i,value;
  	sockfd=socket(AF_INET,SOCK_STREAM,0);
   	if(sockfd==-1)
 	{
  		perror("\n SOCKET ERROR");
   		exit(1);
 	}
 	seraddr.sin_family=AF_INET;
 	seraddr.sin_addr.s_addr=INADDR_ANY;
 	seraddr.sin_port=htons(PORTNO);
 	status=bind(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr));
	if(status==-1)
	{
		perror("\n BIND ERROR");
		exit(1);
	}
	status=listen(sockfd,1);
	if(status==-1)
	{
		perror("\n SERVER ERROR");
		exit(1);
	}
	clien=sizeof(clien);
	newsockfd=accept(sockfd,(struct sockaddr*)&cliaddr,&clien);
 	while(1)
	{
 		read(newsockfd,buf,sizeof(buf));
    	if(strcmp(buf,"QUIT\n")==0)
    		break;
		printf("Client: %s",buf);
		memset(buf,0,256);
		printf("You: ");
		fgets(ch,256,stdin);
		ch[strlen(ch)]='\0';
		write(newsockfd,ch,strlen(ch));
		if(strcmp(ch,"QUIT\n")==0)
			break;
		memset(ch,0,256);
	}
	return 0;
}
