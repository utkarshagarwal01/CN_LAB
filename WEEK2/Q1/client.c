#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
int main()
{
	int len,result,sockfd,n=1;
	struct sockaddr_in address;
	char ch[256],buf[256];
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("172.16.59.93");
	address.sin_port=htons(10212);
	len = sizeof(address);
	result=connect(sockfd,(struct sockaddr *)&address,len);
	if(result==-1){
		printf("errorr");		
		perror("\nCLIENT ERROR");
		exit(1);
	}
	printf("\nENTER STRING\t");
	fgets(ch,256,stdin);
	ch[strlen(ch)]='\0';
	write(sockfd,ch,strlen(ch));
	printf("STRING SENT BACK FROM SERVER IS .....");
	while(n){
		n=read(sockfd,buf,sizeof(buf));
		if(n==-1)
			perror("Error while reading output");
		puts(buf);
	}
	return 0;
}
