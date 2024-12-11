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

//This function use it for wildcard
int size(char *p);
int wildcardCheck(char *file);
int lastwordcheckCat(char *a,char *u);
int matchWord(char *a,char *u,int t);

int checkstr(char *a,char *p,int s);

//This cat function is an read a file if there is a wildcard or not 
void cat(char *a){

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
		
	//This if statement check if falid of open directiry otherwise store all file and directory into array
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
	}if(a==0){

		printf("No such file\n");

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
                                                                	k=1;
                                                         		printf("Reading File: %s\n",u[i]);
                                                                	stat(u[i],&fileS);
                                                             
                                                               	char *buf=(char*)malloc(fileS.st_size * sizeof(char));
                                                               		 while(s=read(fd,buf,fileS.st_size)>0){
                                                                	}

                                                                	//I am using for loop here to print content of object files 
                                                                	for(int i=0; i<fileS.st_size; i++){
                                                   		 	      printf("%c",buf[i]);
                                                    	    		}
                                                    			dd=close(fd);
                                             		        	free(buf);
                                                                	buf=NULL;
								}
							    }else{
								printf("This is a directory\n");
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

		//If file not exist the print a massage
                if(check != 1){
                       printf("No such file or directory\n");
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
                                                                        printf("Failed of opening file\n");
                                                                }else{
                                                                        nextline=1;
                                                                        k=1;
                                                                        stat(u[i],&fileS);
									printf("Reading File: %s\n",u[i]);
                                                                        char *buf=(char*)malloc(fileS.st_size * sizeof(char));

                                                                        while(s=read(fd,buf,fileS.st_size)>0){
                                                                        }

                                                                        //I am using for loop here to print content of object files
                                                                        for(int i=0; i<fileS.st_size; i++){
                                                                                 printf("%c",buf[i]);
                                                                        }
                                                                        dd=close(fd);                                                                                                                free(buf);
                                                                        buf=NULL;
                                                                         ch=NULL;
                                                                }
								//Else statement that print a massage f it is a directory
                                                        }else{
                                                                k=1;
                                                                printf("%s: Is a directory\n",u[i]);

                                                        }
                                                        k=1;
                                                }
                                        }

                                }
                        }
                }
		//print this massage if there is no file
                if(k!=1){
                        printf("No such file\n");
                }
	//This if statemnt run if at the end of file  
	}else if(wildcardCheck(a)==3){
		
		int ga=size(a)-1;
                int k=0;
                int mm=0;
                int rr=0;
		char savedF[1024][1024];
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
							//If statemnet check if file was opened or not 
							if(fd==-1){
                                                                        printf("Failed of opening file\n");
                                                       }else{
							       printf("Reading File: %s\n",u[i]);
								nextline=1;
								k=1;
                	                                	stat(u[i],&fileS);
							
						
								char *buf=(char*)malloc(fileS.st_size * sizeof(char));
								while(s=read(fd,buf,fileS.st_size)>0){
                               					}
                                			
								//I am using for loop here to print content of object files 
                             		  			for(int i=0; i<fileS.st_size; i++){
                                       					 printf("%c",buf[i]);
                                				}
                              					dd=close(fd);
								free(buf);
                						buf=NULL;
               							ch=NULL;
							}
          	                             	}else{
						 	k=1;
							printf("%s: Is a directory\n",u[i]);
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
                        printf("No such files\n");
                }
	

	//This code run if there is no wildcard and print a wriiten file  
	}else{
		//open the file and read content
		struct stat fileStat;
       		stat(a,&fileStat);
		DIR *de;
        	int alocatedSize =fileStat.st_size;
		struct stat fileS;
       		char *buf=(char*)malloc(alocatedSize * sizeof(char));
        	int k=0;
		ch=buf;
        	fd=open(a,O_RDONLY);


		//If statement run if failde of open the file
		if(fd==-1){
                                      printf("Failed of opening file\n");
               }else{
		clFile=&fd;
		 
		de=opendir(a);

  //This part check if file is opened thant read content and print it into screen otherwise print is an directorye

			if(de==0){
			       printf("Reading File: %s\n",a);
        	 	       while(s=read(fd,buf,alocatedSize)>0){
                	       }
				k=1;
				//I am using for loop here to print content of object files 
				for(int i=0; i<alocatedSize; i++){
					printf("%c",buf[i]);
				}
				dd=close(fd);
				clFile=NULL;
        			if(dd<0){
                			printf("Failed of close file\n");
        			}
			}else{
				k=1;
				printf("%s: Is an directory\n",a);	
			}

			 //If there is no file or directory run this if statement 
      			if(k!=1){
	
               		 printf("%s: No such file .\n",a);

			}
		
		free(buf);
		buf=NULL;
		ch=NULL;
	       }
	}
		

}
