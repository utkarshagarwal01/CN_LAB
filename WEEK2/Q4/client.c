#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>

int main()
{
	int len,result,sockfd,n=1;
	struct sockaddr_in address;
	char ch[256],buf[256];memset(buf,0,256);memset(ch,0,256);

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
	perror("SERVER ERROR\n");
	exit(1);
	}
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	address.sin_port=htons(10355);
	len=sizeof(address);
	result=connect(sockfd,(struct sockaddr *)&address,len);
	if(result==-1)
	{
	perror("CLINET ERROR\n");
	exit(1);
	}


	printf("Enter a String:\n");
	fgets(buf,256,stdin);
	write(sockfd,buf,strlen(buf));
	
	printf("Enter word to be replaced");
	memset(buf,0,256);
	fgets(buf,256,stdin);
 	write(sockfd,buf,strlen(buf));
	
	printf("Enter new word");
	memset(buf,0,256);
	fgets(buf,256,stdin);
 	write(sockfd,buf,strlen(buf));

	memset(ch,0,256);
	n = read(sockfd,ch,sizeof(ch));
	printf("%s\n",ch);
 return 0;

}
