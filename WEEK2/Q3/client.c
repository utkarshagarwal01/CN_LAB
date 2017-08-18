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
  	int len,result,sockfd,n=1;
  	char ch[265],buf[256];
 	struct sockaddr_in address;
  	sockfd=socket(AF_INET,SOCK_STREAM,0);
   	if(sockfd==-1)
 	{
  		perror("\n SOCKET ERROR");
   		exit(1);
 	}
 	address.sin_family=AF_INET;
 	address.sin_addr.s_addr=INADDR_ANY;
 	address.sin_port=htons(PORTNO);
 	result=connect(sockfd,(struct sockaddr *)&address,sizeof(address));
	if(result==-1)
	{
		perror("\n CONNECT ERROR");
		exit(1);
	}
	while(1)
	{
		printf("You: ");
		fgets(ch,256,stdin);
		ch[strlen(ch)]='\0';
		write(sockfd,ch,strlen(ch));
		if(strcmp(ch,"QUIT\n")==0)
			break;
		memset(ch,0,256);
 		read(sockfd,buf,sizeof(buf));
    	if(strcmp(buf,"QUIT\n")==0)
    		break;
		printf("Server: %s",buf);
		memset(buf,0,256);
	}
	return 0;
}
