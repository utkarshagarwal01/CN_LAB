#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#define PORTNO 10212
int main()
{
	int len,sockfd;
	struct sockaddr_in address;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	address.sin_port=htons(PORTNO);
	len = sizeof(address);
	char ch[25],buf[25];	

	printf("Enter two numbers and an operator: ");
	fgets(ch,256,stdin);
	ch[strlen(ch)-1]='\0';
	int m = sendto(sockfd,ch,sizeof(ch),0,(struct sockaddr*)&address,len);

	int n=recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&address,&len);
	puts(buf);
	return 0;
}
