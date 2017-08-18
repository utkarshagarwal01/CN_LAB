#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <error.h>
#define PORTNO 10218
int main()
{	
	int sockfd,newsockfd,portno,clilen,n=1,x;
	char buf[256],ch[256],word[256],error[256]="Word not found";
	memset(buf,0,256);memset(ch,0,256);memset(word,0,256);

	struct sockaddr_in seraddr,cliaddr;
	int i,value;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	seraddr.sin_family=AF_INET;
	seraddr.sin_addr.s_addr=INADDR_ANY;
	seraddr.sin_port=htons(PORTNO);
	int reuse=-1;
	setsockopt(sockfd,SOL_SOCKET, SO_REUSEADDR, &reuse,sizeof(int));
	n=bind(sockfd,(struct sockaddr*)&seraddr,sizeof(seraddr));
	if(n<0)	perror("Bind Error: ");
	n=listen(sockfd,1);
	if(n<0)	perror("Listen Error: ");
	clilen=sizeof(clilen);
	while(1)
	{
		newsockfd=accept(sockfd,(struct sockaddr*)&cliaddr,&clilen);
		if(newsockfd<0) perror("Accept Error: ");
		if(fork()==0)
		{	
			printf("Sentence sent from client is..\n");
			read(newsockfd,buf,sizeof(buf));
			buf[strlen(buf)-1]='\0';	
			read(newsockfd,ch,sizeof(ch));
			ch[strlen(ch)-1]='\0';		
			read(newsockfd,word,sizeof(word));
			word[strlen(word)-1]='\0';	

			char* pos_char = strstr(buf,ch);
			if(pos_char == NULL)
				write(newsockfd,error,sizeof(error));	
			else
			{
				int pos = pos_char - buf;
				int diff = strlen(word)-strlen(ch);
				int newpos = strlen(buf)+diff;				
				if(diff>0)
				{		
					for(i=newpos;i>=pos+strlen(word);i--)
						*(buf+i)=*(buf+i-diff);
				}
				else if(diff<0)
				{
					for(i=pos+strlen(ch);i<=strlen(buf);i++)
						*(buf+i+diff)=*(buf+i);
				}
				i=0;
				while(*(word+i)!='\0')
				{
					*(buf+i+pos)=*(word+i);
					i++;			
				}
				puts(buf);
				int x=getpid();
				sprintf(ch,"\nPort: %d\n",x);
				
				write(newsockfd,strcat(buf,ch),1000);						
			}
		}
	}

	return 0;

}

