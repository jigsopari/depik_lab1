#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//#define SRV_IP_ADRS "127.0.0.1"
//#define SRV_TCP_PORT 8000
#define MAX_MSG 100

void errExit(char *str)
{
   puts(str);
   exit(0);
}

int main()
{
   int                sockFd;
   char               txmsg[MAX_MSG];
   char               rxmsg[MAX_MSG];
   char               ipaddr[20];
   int                n,srvport;
   struct sockaddr_in srvAdr;

   if((sockFd=socket(AF_INET,SOCK_STREAM,0)) < 0)
      errExit("can't open stream socket\n");
   printf("sock fd:%d\n",sockFd);

   printf("Enter servet port Number:");
   scanf("%d",&srvport);

   printf("Enter server ip address:");
   scanf("%s",ipaddr);
   
   memset(&srvAdr,0,sizeof(srvAdr));
   srvAdr.sin_family = AF_INET;
   srvAdr.sin_addr.s_addr = inet_addr(ipaddr);
   srvAdr.sin_port = htons(srvport);

   if( connect(sockFd,(struct sockaddr *)&srvAdr,sizeof(srvAdr)) < 0)
     errExit("Can't connect to server\n");
  //connect(sockFd,(struct sockaddr *)&srvAdr,sizeof(srvAdr));
   while(1)
   {
     printf("Enter message to send, Enter # to exit:\n");
     __fpurge(stdin);
     fgets(txmsg,MAX_MSG,stdin);
     if(txmsg[0] == '#')
       break;

     n = strlen(txmsg) + 1;
     if(send(sockFd,txmsg,n,0) != n)
       errExit("send error\n");
    /* n = recv(sockFd, rxmsg, MAX_MSG, 0);
     if(n < 0)
       errExit("recv error\n");

     printf("Received following message:\n%s\n",rxmsg);*/
   }
   close(sockFd);
}   
 
  
