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
#include <string.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#define MAXLINE 1024
#define MAXSARRAY 1000000
char *dataS[MAXSARRAY];
int sizes[MAXSARRAY];
int y=0;

//This function print the saved file into array 
void ReadSaved(){

	for(int i=0; i<y; i++){
		
               	 printf("%s",dataS[i]);
      
	}
}
char *ReadAllFile(int fd,char *buffer,int size);
void WriteAllFile(int fd,char *buffer,int size);
void ReadAllFilePrint(int fd,char *buffer,int size);
int open_clientfd(char *hostname, char *port);


int size(char *a){
        int i=0;

        while(a[i]!='\0'){
                i++;
        }
        return i-1;

}
//This function check if read or write falid then exit the server
int Check(int x){
	if(x<0){
		printf("Faild of Read from clinet or Send\n#i");
		printf("Exiting Server.....\n");
		exit(1);
	}

}
char *Filename;
int CreateF=1;
void ChangeFileName(char *File,int sizze){

	int fd=open(Filename,O_WRONLY);
	


	char *new=(char*)malloc(sizeof(char)*((sizze)+2));

	memset(new,'\0',sizze+2);

	char temp[2];

	temp[0]='1';
	temp[1]='.';
	int index=0;
	int ck=0;

	for(int i=0; i<2; i++){
		new[i]=temp[i];
		index=i;
	}
	index++;

	for(int i=0; i<sizze; i++){
                new[index]=File[i];

               index++;
       }
	int k=2;
		while(1){
			int fd=open(new,O_WRONLY);
			if(fd>0){
				   
			   new[0]='0'+k;
			   k++;
			   close(fd);
			}else{
			Filename=new;
			break;
		
		}
			    
		Filename=new;

		}
//		printf("The size %s \n",Filename);
	}
int seek=0;
void WriteToFile(char *data,int sizze){
	
	
		 int fd=open(Filename,O_WRONLY);
		 lseek(fd,seek,SEEK_SET);

		 if(fd<0){
		 	printf("Falied to write into file\n");
		 	return;
		 }
		 int r=sizze;
		 int f=0;
		while(r>0){
		
			f=write(fd,data,1000);
			if(f==0){
				break;
			}
			r-=f;
		}
		seek+=sizze;

		close(fd);



}
int doneCreate=1;

void CreateFile(char *File,int size){

	int fd = open(File,O_RDWR);
	int fd1;
	int fd2;	

	//ChangeFileName(File,size);
//	printf("The New Name Is %s\n",Filename);
	
	if(fd<0){
		
		 fd1=open(File,O_CREAT|O_WRONLY,S_IRUSR |S_IWUSR);
                    if(fd1<0){
                        printf("Error to create file\n");
                    }
	      
		Filename=File;
		
		//printf("This file does not exist %s\n",Filename);
		//doneCreate=0;

	}else{
		
		 ChangeFileName(File,size);	
		  fd2=open(Filename,O_CREAT|O_WRONLY,S_IRUSR | S_IWUSR);
                  if(fd2<0){
                        printf("Error to create file\n");
                    }
		// printf("The New Name Is %s\n",Filename);
		    

		//doneCreate=0;
	}	


}
void receive_reply(int fd, char *a){
	
	
	
	char *data;
	int breakk=1;
	int vd=0;
	int flag=1;
	char *p;
	DIR *d;
	while(flag){

		Check(read(fd,&vd,sizeof(int)));	
		data=(char*)malloc(vd*sizeof(char));
		
		p=ReadAllFile(fd,data,vd);	
	 	Check(read(fd,&flag,sizeof(int)));
		
		if(flag==4){
			seek=0;
		
//			printf("OK%s\n",p);
			//	d=opendir(p);
		//	if(d==0){
			//	printf("This is an directory %s\n",p);
		//	}else{
		//	     printf("%s\n",p);	
			     Filename=p;
                             CreateFile(p,size(p)+1);
				
		//	}
		}else if(flag==2){
			
			WriteToFile(p,size(p));
			
		}else if(flag==3){
			
			  printf("Shutting down the connections....\n");
       			  printf("Exiting....\n");
       			  exit(1);
		}					
	}
	free(data);
}
void send_cmd(int confd, char *a, int size){
	
	

	char *send=(char*)malloc(size*sizeof(char));	
	
	for(int i=0; a[i]!='\0'; i++){
		send[i]=a[i];
	}
	
	
	Check(write(confd,send,1024));


}
int CA=0;
void SIGINT_handle(int signale){
	char f[1024];
	
	memset(f,'\0',1024);

        printf("\n");     	
	for(int i=0; i<y; i++){
          	free(dataS[i]);
        }

	f[0]='9';

	Check(write(CA,f,1024));
	printf("Shutting down the connections....\n");
	printf("Exiting....\n");
	exit(1);
}

int main(int argc, char **argv) {
    int clientfd;
    char command[1024];
    char *host, *port, buf[MAXLINE];
    char aa[1024];
  
    if(signal(SIGINT,SIGINT_handle)==SIG_ERR){
            perror("Faild of Caugh Signale\n");

    }
    memset(command,'\0',sizeof(command));
    if(argc!=3){
	exit(1);
    }
    host = argv[1];
    port = argv[2];
    clientfd = open_clientfd(host, port);
    CA= clientfd;

    while(1){
	printf(">");

	fgets(command,1024,stdin);
 	send_cmd(clientfd,command,size(command));
     	receive_reply(clientfd,aa);

    }
    close(clientfd);
    exit(0);
}

