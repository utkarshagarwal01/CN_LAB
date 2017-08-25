#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#define PORTNO 10212
int main()
{
	int sockfd,num1,num2;
	char buf[256],oprtr;
	struct sockaddr_in seraddr,cliaddr;
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	seraddr.sin_family = AF_INET;
	seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	seraddr.sin_port = htons(PORTNO);
	int result = bind(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr));
	if(result == -1) perror("Bind Error");	
	int clilen = sizeof(cliaddr);
	int m = recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&cliaddr,&clilen);
	sscanf(buf," %d %d %c",&num1,&num2,&oprtr);
	float answer=0;	
	if(oprtr == '+')
		answer=num1+num2;
	else if (oprtr == '-')
		answer=num1-num2;
	else if (oprtr == '*')
		answer=num1*num2;
	else if (oprtr == '/')
		answer=(float)num1/num2;
	memset(buf,0,256);	
	sprintf(buf,"%f",answer);
	int n = sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&cliaddr,clilen);
	puts(buf);	
	return 0;
}
