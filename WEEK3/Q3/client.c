#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <unistd.h>
int main()
{
	int len,result,sockfd,n=1;
	struct sockaddr_in address;
	char ch[256],buf[256];memset(buf,0,256);memset(ch,0,256);
int reuse=-1;
	setsockopt(sockfd,SOL_SOCKET, SO_REUSEADDR, &reuse,sizeof(int));
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	address.sin_port=htons(10218);
	len=sizeof(address);
	result=connect(sockfd,(struct sockaddr*)&address,len);
	if(result<0)
	{
		perror("\n CLIENT ERROR");
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
