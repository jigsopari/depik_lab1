#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SRV_IP_ADRS "127.0.0.1"
#define SRV_TCP_PORT 8000
#define MAX_MSG 100
#define IN_STOP_CHARACTER '#'

void errExit(char *str)
{
   puts(str);
   exit(0);
}

int main(void)
{
   int                sockFd;
   struct sockaddr_in srvAdr;
   char               txmsg[MAX_MSG];
   char               rxmsg[MAX_MSG];
   int                n;

   if((sockFd=socket(AF_INET,SOCK_STREAM,0)) < 0)
      errExit("can't open stream socket\n");
   printf("sock fd:%d",sockFd);
   memset(&srvAdr,0,sizeof(srvAdr));
   srvAdr.sin_family = AF_INET;
   srvAdr.sin_addr.s_addr = inet_addr(SRV_IP_ADRS);
   srvAdr.sin_port = htons(SRV_TCP_PORT);

   if( connect(sockFd,(struct sockaddr *)&srvAdr,sizeof(srvAdr)) < 0)
     errExit("Can't connect to server\n");
  //connect(sockFd,(struct sockaddr *)&srvAdr,sizeof(srvAdr));
   while(1)
   {
     printf("Enter message to send, Enter # to exit:\n");
     fgets(txmsg,MAX_MSG,stdin);
     if(IN_STOP_CHARACTER == txmsg[0])
       break;

     n = strlen(txmsg) + 1;
     if(send(sockFd,txmsg,n,0) != n)
       errExit("send error\n");
     n = recv(sockFd, rxmsg, MAX_MSG, 0);
     if(n < 0)
       errExit("recv error\n");

     printf("Received following message:\n%s\n",rxmsg);
   }
   close(sockFd);
	 return 0;
}   
 
  