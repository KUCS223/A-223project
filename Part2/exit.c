#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

//This checks if the file are free or not
extern char *ch;
extern int *clFile;
extern int *ServerFd;
extern int *ClinetFd;
void send_reply(int fd, char *a,int size);
void WriteExit(int fd,int flag);

extern int ClinetConnection;
//The ClineEx varriable determine if is 9 then clinet write exist and want to close connection otherwise close the server
extern int ClineEx;

//This funtion if user click cntorl-C
void exist(int connfd){


        int x;
        // if check if filed not freed than free it 
        if(ch!=NULL){

                free(ch);
                ch=NULL;

        }
        // if check if filed not closed than close it 
        if(clFile!=NULL){

                x=close(*clFile);
                if(x<0){
                        printf("Failed of close file\n");
                }
        } 
		if(ClinetFd!=0){
			
			//Send for the clint with flag 3 to close the client	
			send_reply(connfd,"\0",1);
			WriteExit(connfd,3);
			
			//close Clinet connection
                	x=close(*ClinetFd);
                	if(x>=0){
				printf("Clinet Exiting program.......\n");
				printf("\nClosing Clinet Connection......\n");
               		 }
			ClinetConnection=1;
       		}

		if(ClineEx==2){
			ClineEx=0;
			return;
		}else{
			printf("Exiting...\n");
                        exit(1);
		}
		
}
