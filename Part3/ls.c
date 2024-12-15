#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
extern char *ch;

//This varraible set it to one if there is wildcard in directory name
int WLS=0;
extern int Send;
//The functions use it for wildcard
int size(char *p);
int wildcardCheck(char *file);
int lastwordcheck(char *a,char *u);
int matchWordLS(char *a,char *u,int t);
void send_reply(int fd, char *a,int size);
void WriteExit(int fd,int flag);

//This function for wildcard in middle that return 1 if mach of the word in current derectory otherwise return 0;
int checkstr(char *a,char *p,int s);


//This ls function list  file if there is a wildcard or not  also can list current file
void ls(char *a, int connfd){

       DIR *d;
       struct dirent *de;
       char *e;
       int chec=1;
       char u[1024][1024]; 
       int t=0;
       int p=0;
       int k=0;
       int rr=0;

       /*This part check if there is directory list it otherwise list a current direc#tory also add checking error*/	       		
	d=opendir(".");
	if(d==0){

		printf("Failed of open directory\n");
	}else{
		while(de=readdir(d)){                                
        	         e=de->d_name;   
                	 for(int j=0; j<size(e); j++){                    
                      		 u[t][j]=e[j];
                      		 if(j+1==size(e)){
                         		 u[t][j+=1]=32;  
                      		 }
                 	}                
                	t++;       
       		}


       }
       /*-------------------------------------------------------------------------------------------------------*/

	/*This if check if there is no directory or file then list current directory or file*/
       if(*a==0){ 
       		d=opendir(".");
		if(d==0){
			send_reply(connfd,"Failed of listing current directory\n",37);
			Send+=37;	
		       	WriteExit(connfd,0);
			 printf("Failed of open directory\n");
		}else{
			printf("Lisiting current direcotry .....\n");
			while(de=readdir(d)){
			     
			
		 
				send_reply(connfd,de->d_name,size(de->d_name));
				Send+=size(de->d_name);

		       			WriteExit(connfd,1);
					send_reply(connfd,"\n",1);
					Send+=1;

					WriteExit(connfd,1);
				
				
			}	

			send_reply(connfd,"\0",1);
			Send+=1; 
			WriteExit(connfd,0);
		}

        //The if cheack if there is wildcard at the end of string 
       }else if(wildcardCheck(a)==3){

	       printf("Listing directiry with using wildcard .......\n");
		                                                                                    
		int ga=size(a)-1;
		int mm=0;
		

		//This for loop check if last wildcard mach the last charector than print file or directory 
		for(int i=0; i<t; i++){
                        e=u[i];
         	        for(int j=0; j<size(e); j++){
        	
				if(a[j]==u[i][j]){
						
					mm++;
					if(mm==ga){
						k=1;
						
						send_reply(connfd,u[i],size(u[i]));	
						Send+=size(u[i]);	
			       			WriteExit(connfd,1);
                                                    send_reply(connfd,"\n",1);
						    Send+=1;
							WriteExit(connfd,1);
						
					}
			       				
				}
                	}				
			mm=0;
                }

		//This check is K equal 1 then there is no directory or file listing 
		if(k!=1){
			send_reply(connfd,"No such file or directory\n",28);
                        Send+=28;
			WriteExit(connfd,0);

			printf("No such file or directory listinging.....\n");	
		}else{
		
			send_reply(connfd,"\0",1);
                	Send+=1;
			WriteExit(connfd,0);
		}
		k=0;
		rr=0;
	
	//The if cheack if there is wildcard at the start of string
	}else if (wildcardCheck(a) == 1){
		
			int sizeA=size(a)-1;
			int check=0;

		//This for loop check if first wildcard mach the first charector of string than print file or directory 
			for(int i=0; i<t; i++){
                	       e=u[i];
			     
                       		 for(int j=1; j<size(e); j++){
                                	if(a[1]==u[i][j]){
		 				int l=j;
						for(int k=1; k<size(a); k++){
							if(a[k]==u[i][l]){
								rr++;
								if(rr==sizeA){
                                                        		if(lastwordcheck(a,u[i])){
                                                				check=1;
									printf("Listing directiry.....\n");	
								       	send_reply(connfd,u[i],size(u[i]));
									Send+=size(u[i]);				
										WriteExit(connfd,1);
                                        	                		send_reply(connfd,"\n",1);
									       Send+=1;	
										
									       	WriteExit(connfd,1);
                                                        
									}		
								}
							}
							l++;

						}	
						rr=0;
                                	}	       
                        	}

                	}
			//If startement check  there is no file or directory
			if(check == 1){	
				send_reply(connfd,"\0",1);
				Send+=1;
                                WriteExit(connfd,0);
			}else{
				  printf("No such fil	e or directory\n");
				  send_reply(connfd,"No such file or directory\n",26);
                                  Send+=26;
				  WriteExit(connfd,0);
			}		
			k=0;
			rr=0;
		
	




	//This Part check if wildcard in middle  	
	}else if(wildcardCheck(a)==2){

		int ga=size(a)-1;
               
                int mm=0;
                int o=0;
		//This for loop check if middle wildcard mach the middle charecters of string than print file or directory
		for(int i=0; i<t; i++){
                        e=u[i];
                        for(int j=0; j<size(a); j++){

                                if(a[j]==42){
							
					int sizx=size(u[i])-2;			
					if(a[0]==u[i][0] && a[ga]==u[i][sizx]){
						

						//This function return 1 if charecters mach the string in current directory
						if(checkstr(a,u[i],ga)){
							 printf("Listing directiry with using wildcard .......\n"); 
							send_reply(connfd,u[i],size(u[i]));
                                           		Send+=size(u[i]);     
					       		WriteExit(connfd,1);
                                                	send_reply(connfd,"\n",1);
							Send+=1;
							WriteExit(connfd,0);
							k=1;
						}
					}		

                                }
                        }
                }

		//If startement check  there is no file or directory
                if(k!=1){
			 send_reply(connfd,"No such file or directory\n",27);
                         Send+=27;
			 WriteExit(connfd,0);
                       printf("No such file or directory listing....\n");
                       
                }	

		k=0;

	//This Part start if there file or directory after ls and print it in screen
	}else{
	
		int sizeOfFile=0;
		int RealSize=size(a);
		char y[size(a)];
                char *f;
                int g=0;

		t=0;

                d=opendir(".");

		//This if check if failed of open directory
		 if(d==0){
                         printf("Failed of open directory\n");
		 }else{
			//Whle loop if file is qual the fil	e in curreent directory than use counter to mach the size than print the name of file  
			int k=0;
			while(de=readdir(d)){
			 	e=de->d_name;
				for(int j=0; j<size(e); j++){
					if(e[j]==a[j]){
						k++;		
					}
					
					if(k==size(e)){
						printf("Listing file or directory....\n");
						send_reply(connfd,a,size(a));
        		                	Send+=size(a);
						WriteExit(connfd,1);
					
						send_reply(connfd,"\n",1);
						Send+=1;
                                                WriteExit(connfd,0);
						g=1;
					}
				
				}
				k=0;
			
			}
			//if there is no file than print massage else print the name of file
			 if(g!=1){
                                send_reply(connfd,"Faild of listing file or directoty",34);
                                Send+=16;
				WriteExit(connfd,1);

				send_reply(connfd,"\n",1);
                                Send+=1;
                                WriteExit(connfd,0);
                                printf("No such file or direectory listing....\n");
                        }


		}
	}
}
