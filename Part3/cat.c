#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

//This checks if the file are free or not 
extern char *ch;
extern int *clFile;

//Send caluculate the send it bytes
extern int Send;

//This function use it for wildcard
int size(char *p);
int wildcardCheck(char *file);
int lastwordcheckCat(char *a,char *u);
int matchWord(char *a,char *u,int t);
void WriteExit(int fd,int flag);
int checkstr(char *a,char *p,int s);
void send_reply(int fd, char *a,int size);

//Send for clinet printing file 
void PrintintFile(int connfd,char *a){

	printf("Printting %s File.....\n",a);
        send_reply(connfd,"Printing File: ",15);
        WriteExit(connfd,1);

        send_reply(connfd,a,size(a));
        WriteExit(connfd,1);

        send_reply(connfd,"\n",1);
        WriteExit(connfd,1);
}


//The function do short read then send it to clinet
void Read(int connfd,char *a,int fd,int ssize){
	
       	int x=0;
        int f=0;
	int r=ssize;
	int ss=1000;
	char *buf=(char*)malloc(sizeof(char)*ss);
	int k=1;
        int sp=0;

	PrintintFile(connfd,a);
	
	while(r>0){
			memset(buf, '\0', ss);			
			f=read(fd,buf,ss);	
                	Send+=f;
			send_reply(connfd,buf,f);
			x+=f;
			WriteExit(connfd,1);
			sp++;
			if(f==0 || f<0){
				break;
			}
			r-=f;;
			ss=f;

	} 
	  free(buf);
	
}

//This cat function is an read a file if there is a wildcard or not 
void ReadingFile(int connfd,char *a){

	send_reply(connfd,"Reading file: ",14);
	Send+=14;
	WriteExit(connfd,1);

        send_reply(connfd,a,size(a));
        Send+=size(a);
	WriteExit(connfd,1);

        send_reply(connfd,"\n",1);
        Send+=1;
	WriteExit(connfd,1);

}




void cat(char *a,int connfd){

	int dd=0;
        int fd;
        int s=0;		
	char u[1024][1024];	
	DIR *d;
        DIR *CH;
        struct dirent *de;
	int t=0;
	char *e;
	int nextline=0;
		
	//This if statement check if falid of open directiry ot	
//herwise store all file and directory into array
	for(int i=0; i<1024; i++){
		for(int j=0; j<1024; j++){
			u[i][j]='\0';
		}
	}
	d=opendir(".");
	if(d==0){
		printf("Error\n");
	}else{
        while(de=readdir(d)){
                 e=de->d_name;
                 for(int j=0; j<size(e); j++){

                            u[t][j]=e[j];	
                 }
                 t++;
	}



	//This if chech if the file not exist
	}if(*a=='\0'){
		
		send_reply(connfd,"No such file\n",13);
		Send+=13;
		WriteExit(connfd,0);
		printf("No such file ......\n");

	//Ths Part check if wildcard is start of string  	
	}else if(wildcardCheck(a)==1){

		int rr=0;
                int sizeA=size(a)-1;
                int check=0;
		struct stat fileS;


                for(int i=0; i<t; i++){
                       e=u[i];		
                       for(int j=1; j<size(e); j++){		 
			     if(a[1]==u[i][j]){
                                  int l=j;
                                  for(int k=1; k<size(a); k++){
                                        if(a[k]==u[i][l]){
                                               rr++;

					       //This if for check of file was wrriten and size in directory if mach than go
                                               if(rr==sizeA){
						//This if for check of last word in string and last word of file in  dirrectory than go     
                                                  if(lastwordcheckCat(a,u[i])){
							  //This Part will open file and read it and print it in screen 
                                                            d=opendir(u[i]);
							    //This if chech if is it directory or file 
                                                	    if(d==0){
								check=1;
                                      	                         fd=open(u[i],O_RDONLY);

								if(fd==-1){
									printf("Failed of opening file\n");
								 }else{
                                                                	nextline=1;
                                                                	stat(u[i],&fileS);                                   
                                          			        Read(connfd,u[i],fd,fileS.st_size);		
									dd=close(fd);
								 }
							    }else{

								 //This Part send to clinet this is directoy
								 send_reply(connfd,u[i],size(u[i]));
                                                                 WriteExit(connfd,1);
								Send+=size(u[i]);
								send_reply(connfd,": Is a directory\n",17);
								Send+=17;
                                                                WriteExit(connfd,0);
								printf("%s: is an directory...\n",u[i]);
							    }
                                                      }
                                                 }
                                          }
                                          l++;

                                    }
                                    rr=0;   
			     }
                       }
                }

		//If file not exist the and send to clinet with print a massage
                  if(check != 1){
             		send_reply(connfd,"No such file or directory\n",26);
                        Send+=26;
			WriteExit(connfd,0);

	      		
			printf("No such file or directory\n");
                }else{
			printf("Printing a File......\n");
			send_reply(connfd,"\0",1);
			Send+=1;
                        WriteExit(connfd,0);
		
		}
		

	//This part check if wildcard is in middle of string 
	}else if(wildcardCheck(a)==2){
	
		struct stat fileS;		
		char *r;
		int k=0;
		DIR *de;
		int ga=size(a)-1;
                int mm=0;
                int o=0;


                //This for loop check if middle wildcard mach the middle charecters of string than print file or directory
                for(int i=0; i<t; i++){
                        e=u[i];
                        for(int j=0; j<size(a); j++){

                                if(a[j]==42){

					//if statement check if the file are mach any file in my current directory
                                        int sizx=size(u[i])-1;
                                        if(a[0]==u[i][0] && a[ga]==u[i][sizx]){
						
                                                //This function return 1 if charecters mach the string in current directory
                                                if(checkstr(a,u[i],ga)){
                                                     
                                                        de=opendir(u[i]);
                                               //This if check if is it file then print it otherwise print is an directory
                                              		  if(de==0){

                                                                fd=open(u[i],O_RDONLY);
                                                                if(fd==-1){
									send_reply(connfd,"No such file\n",13);
                                                                        printf("Failed of opening file\n");
                                                                }else{
									//This Part send the file to clinet
                                                                        nextline=1;
                                                                        k=1;
                                                                        stat(u[i],&fileS);
									 Read(connfd,u[i],fd,fileS.st_size);		  
                                                                        dd=close(fd);                                                                                                               
                                                                         ch=NULL;
                                                                }
								//Else statement that print a massage f it is a directory
                                                        }else{
                                                                k=1;
							
								//This Part send to clinet this os an directory
								send_reply(connfd,u[i],size(u[i]));
								Send+=size(u[i]);
                                                                WriteExit(connfd,1);
                                                                send_reply(connfd,": Is a directory\n",17);
                                                                Send+=17;
								WriteExit(connfd,1);
								
								printf("%s: Is an directory....\n",u[i]);
                                                        }
                                                        k=1;
                                                }
                                        }

                                }
                        }
                }
		//print and send to clinet this massage if there is no file
                if(k!=1){
			
			send_reply(connfd,"No such file or directry\n",25);
			Send+=25;
                        WriteExit(connfd,0);
                        printf("No such file or directory\n");

                }else{
			//Send to clinet there is not ))data to stop the loop
			 send_reply(connfd,"\0",1);
			 Send+=1;
                         WriteExit(connfd,0);
		}
	//This if statemnt run if at the end of file  
	}else if(wildcardCheck(a)==3){
		
		int ga=size(a)-1;
                int k=0;
                int mm=0;
                int rr=0;
		struct stat fileS;
               	

		//For goes entire file in array and check if is equal of the file using size
                for(int i=0; i<t; i++){
                        e=u[i];
                        for(int j=0; j<size(e); j++){

                                if(a[j]==u[i][j]){

                                        mm++;
					//If statemet run if size of file mach the size of file in currne directory 
                                        if(mm==ga){
                                             
						d=opendir(u[i]);
						 //This if check if is it file then print it otherwise print is an directory
						if(d==0){

							fd=open(u[i],O_RDONLY);
							//If statemnet checkda if file was opened or not 
							if(fd==-1){
									send_reply(connfd,"No such file\n",13);
                                                                        printf("Failed of opening file...\n");
                                                       }else{
							//This part send data to clinet
								nextline=1;
								k=1;
                	                                	stat(u[i],&fileS);
								Read(connfd,u[i],fd,fileS.st_size);
                              					dd=close(fd);
               							ch=NULL;
							}
          	                             	}else{
							//This Part send to clinet this os an directory
						 	k=1;
					                send_reply(connfd,u[i],size(u[i]));
							Send+=size(u[i]);
                                                        WriteExit(connfd,1);				
							send_reply(connfd,": Is an directory\n",18);
							Send+=18;
							WriteExit(connfd,1);
							printf("%s: Is a directory......\n",u[i]);
					   }
	
                                	}
                	        }
                       
                	}
			mm=0;
		}
		
		if(nextline==1){
			printf("\n");
		}
		//If there is no file or directory run this if statement 
                if(k!=1){

			send_reply(connfd,"No such file\n",13);
			Send+=13;
                        WriteExit(connfd,0);
			printf("No such files...\n");
                }else{
			    send_reply(connfd,"\0",1);
			    Send+=1;
                            WriteExit(connfd,0);
		
		}
	

	//This code run if there is no wildcard and print a wriiten file  
	}else{
	
		//open the file and read content
		struct stat fileStat;
       		stat(a,&fileStat);
		DIR *de;
        	int alocatedSize= fileStat.st_size;
		struct stat fileS;
        	int k=0;

        	fd=open(a,O_RDONLY);
		//If statement run if failde of open the file
		if(fd==-1){

		        send_reply(connfd,"No such file\n",13);
			Send+=13;
	                WriteExit(connfd,0);
                        printf("No such file...\n"  );


               }else{
			clFile=&fd;	 
			de=opendir(a);
  	//This part check if file is opened thant read content and print it into screen otherwise print is an directorye
			if(de==0){

				//This function read afile using short read and send it to clinet        	 	     				
				Read(connfd,a,fd,alocatedSize);
         			send_reply(connfd,"\0",1);
          			WriteExit(connfd,0);       
				k=1;
 				
				dd=close(fd);
				clFile=NULL;
        			
				if(dd<0){

                			printf("Failed of close file\n");
        				send_reply(connfd,"Failed of close file\n",21);
                                	 Send+=21;
					WriteExit(connfd,0);
				}
			}else{
				//This Part send to clinet this is an directory

				k=1;
				send_reply(connfd,"Is an directory\n",16);
				 Send+=16;
				WriteExit(connfd,0);
				printf("Faild open it is an directory...\n");
			}

			 //If there is no file or directory run this if statement 
      			if(k!=1){
	
				 send_reply(connfd,"No such file",13);
				 Send+=13;
        	       		 WriteExit(connfd,0);
				 printf("No such file...\n");

			}
		ch=NULL;
	       }
	}
		

}
