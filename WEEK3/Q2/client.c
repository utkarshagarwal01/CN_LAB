#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main()
{
	int len,result,sockfd,n=1;
	struct sockaddr_in address;
	char ch[256],buf[256];memset(buf,0,256);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
		perror("SocketError");
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	address.sin_port=htons(10275);
	len = sizeof(address);
	result=connect(sockfd,(struct sockaddr *)&address,len);
	if(result==-1)
		perror("\nCLIENT ERROR\n");
	write(sockfd,ch,2);
	while(n)
	{
		fflush(stdout);
		n=read(sockfd,buf,sizeof(buf));
		fflush(stdout);
		if(n==-1)	perror("Error while reading output");
		if(n==0)	printf("Exiting");
		puts(buf);
		memset(buf,0,256);
	}
	return 0;
}
