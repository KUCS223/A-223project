#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


void send_reply(int fd, char *a,int size);
void WriteExit(int fd,int flag);

//This function print help menu
void help(int connfd){

	char buf[236]="help: print a help menu\nls: list files in current remote directory\nls *.txt: list text files\ncat: output file contents\nret filename: retrieve filename\nret *.txt: retrieve all text files\nstat: print statistics\nexit: exit the file server";


		int i=0;

		while(buf[i]!='\0'){

			i++;
		}
		printf("Printing help menu .....\n");

		send_reply(connfd,buf,i);
		WriteExit(connfd,0);




	
}

