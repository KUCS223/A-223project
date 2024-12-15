#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

void WriteExit(int fd,int flag);
void send_reply(int fd, char *a,int size);
int size(char *a);

//These global varrible for stats function to calucalute
extern int TotalAccept;
extern int Send;
extern int TotalfileDownload;
extern int TotalFileByteDown;

void stats(int connfd,char *a){

	char p[1000];
	
	printf("Running states function.....\n");

	//This Part send total clinet accept connection
	memset(p,'\0',1000);	
	sprintf(p,"%d",TotalAccept);
	send_reply(connfd,"The total clinet accept connection are: ",40);
	WriteExit(connfd,1);
	send_reply(connfd,p,size(p));
        WriteExit(connfd,1);
	send_reply(connfd,"\n",1);
        WriteExit(connfd,1);
	
	//This Part send Total file downloaded
	memset(p,'\0',1000);
        sprintf(p,"%d",TotalfileDownload);
        send_reply(connfd,"Total file downloaded: ",23);
        WriteExit(connfd,1);
        send_reply(connfd,p,size(p));
        WriteExit(connfd,1);
        send_reply(connfd,"\n",1);
        WriteExit(connfd,1);
	
	//This Part to send for cllinet Total bytes file that downloading
	memset(p,'\0',1000);
        sprintf(p,"%d",TotalFileByteDown);
        send_reply(connfd,"The total bytes that downloaded from file Server: ",50);
        WriteExit(connfd,1);
        send_reply(connfd,p,size(p));
        WriteExit(connfd,1);
        send_reply(connfd,"\n",1);
        WriteExit(connfd,1);


	//This Part to send for cllinet  Total bytes the reading from file
	memset(p,'\0',1000);
        sprintf(p,"%d",Send);
        send_reply(connfd,"The Total bytes received: ",26);
        WriteExit(connfd,1);
        send_reply(connfd,p,size(p));
        WriteExit(connfd,1);
	send_reply(connfd,"\n",1);
        WriteExit(connfd,0);	




}
