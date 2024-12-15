//ALI ALKHULAIFI 2212172438
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <sys/stat.h>

#define MAXLINE 1024
int *ServerFd=0;
int *ClinetFd=0;

//These global varrible for stats function to calucalute
int TotalAccept=0;
int Send=0;
int TotalfileDownload=0;
int TotalFileByteDown=0;

//Commands functions 
void ls(char *a,int connfd);
void cat(char *a,int connfd);
void exist(int x);
void help(int connfd);
void retrieves(char *a,int connfd);
void stats(int connfd,char *a);

char *ch;
int *clFile;
int ClineEx=0;

//Function that do short read and write
void ReadAllFile(int fd,char *buffer,int size);
void WriteAllFile(int fd,char *buffer,int size);
void WriteExit(int fd,int flag);
int size(char*);



void send_reply(int fd, char *a,int size);

//This function handle a control c and call exist function
void SIGINT_handle(int signale){

        printf("\n");
        exist(signale);
}

typedef struct sockaddr SA;
int open_listenfd(char *port);

int paarse_cmd(char *a){
        char x[]="help";
        char y[]="ls";
        char z[]="cat";
        char c[]="exit";
 	char s[]="stat";
	char r[]="ret";
 	int xn=0;
        int yn=0;
        int zn=0;
        int cn=0;
	int sn=0;
	int rn=0;
        int i=0;    	
	//while loop to check if there is space or newline set it to zero 
        while(a[i]!=0){
                if(a[i]==32|| a[i]==10){
                      a[i]=0;
                }
                i++;
        }
        i=0;

        while(a[i]!=0){

                if(a[i]==x[i]){
                        xn++;
                }
                if(a[i]==y[i]){
                        yn++;
                }
                if(a[i]==z[i]){
                        zn++;
                }
                if(a[i]==c[i]){
                        cn++;
                }
		if(a[i]==s[i]){
			sn++;
		}
		if(a[i]==r[i]){
			rn++;
		}
               i++;
	}
        if(xn==4&& i==xn){
                return 1;
        }else if(yn==2 && i==yn){

                return 2;

        }else if(zn ==3 && i==zn){
                return 3;

        }else if(cn == 4 && i==cn){

                return 4;

	}else if(sn == 4 && i==sn){
		return 5;

	}else if(rn == 3 && i==rn){
		return 6;
        }else{
                return 0;
        }
}
void encrypt(char *original, char *encrypted,int size){

	for(int i=0; i<size; i++){
	
		encrypted[i]=original[i]+5;
	
	}



}
void send_reply(int fd, char *a,int size){
	
	int num=size;
 	write(fd,&num,sizeof(int));

	char *p;
	p=(char *)malloc(sizeof(char)*size);

	encrypt(a,p,size);
	WriteAllFile(fd,p,size);

}
int ClinetConnection=0;
void receive_cmd(int connfd,char *a){
	
	
	char f[1024];
        int i=0;
        int s=0;
        char file[1024];
        int r=0;
        int l=0;
        char command[1024];

	for(int i=0; i<1024; i++){
                file[i]='\0';
		f[i]='\0';
		command[i]='\0';
	}		

        if(signal(SIGINT,SIGINT_handle)==SIG_ERR){
            perror("Faild of Caugh Signale\n");
	     ClinetFd=&connfd;
	  
        }

	int  g=1;
	int ck=0;
	int vd;


	read(connfd,f,1024);

	//This flage to close clinet connection
	if(f[0]=='9'){
		printf("\nClosing Clinet Connection......\n");
		ClinetConnection=1;	
		return;			
		
	}	
	while(f[i]!='\0'){
                     //This if statment wait until word reach the space than store the file in array 
                        if(s){
                              file[r]=f[i];
                              if(file[r]==32|| file[r]==10){
                                        file[r]=0;
                              }
                              r++;
                        //Store the command word into command array      
                        }else{
                              command[l]=f[i];
                              file[l]=0;
                              l++;
                        }
                        //This if set s to 1 if there is space 
                        if(f[i]==32){
                                 s++;
                         }

                          i++;
	 }
	 if(paarse_cmd(command)==1){
                 help(connfd);
         }else if(paarse_cmd(command)==2){
                 ls(file,connfd);
         }else if(paarse_cmd(command)==3){
                 cat(file,connfd);
         }else if(paarse_cmd(command)==4){
		 ClineEx=2;                 	 
		 exist(connfd);
         }else if(paarse_cmd(command)==5){
	      
	       	 stats(connfd,file);
	      
	 }else if(paarse_cmd(command)==6){
			
		retrieves(file,connfd);
	 }else{
		send_reply(connfd,"command not found",20);	
		Send+=20;
		WriteExit(connfd,1);
		send_reply(connfd,"\n",1);
                Send+=1;
		WriteExit(connfd,0);
		printf("Resevied command does not found....\n");
   			
	      }
}

int main(int argc, char **argv){

    char string[200];
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;  
    char client_hostname[MAXLINE], client_port[MAXLINE];
    char *p;
    
    if(signal(SIGINT,SIGINT_handle)==SIG_ERR){
            perror("Faild of Caugh Signale\n");

    }
    if(argc != 2){
	      exit(1);
    }
    listenfd = open_listenfd(argv[1]);
    while(1){
	      clientlen = sizeof(struct sockaddr_storage); 
	      connfd = accept(listenfd, (SA *)&clientaddr, &clientlen);	
	      TotalAccept+=1; 
              getnameinfo((SA *) &clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
       	      ClinetConnection=0;	
	      ClinetFd=&connfd;

              printf("Server connected to client (%s, %s)\n\n", client_hostname, client_port);
	      while(1){
		  receive_cmd(connfd,p);
		  if(ClinetConnection){
		         ClinetFd=0;
			 break;
		   }
	      }
              Send=0;
	      TotalfileDownload=0;
	      TotalFileByteDown=0;
	      close(connfd);

    }
    exit(0);
}
