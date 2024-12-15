#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int q=1;

void ReadAllFile(int fd,char *buffer,int size){
	
	int breakk;
	int vd=size;
	char *s="This is retrevie function shutdown printf 2232";
	char *sw="Start again printf";
	
	buffer=(char*)malloc(vd*sizeof(char));

//	char *buf=(char*)malloc(sizeof(char)*vd);	

	int sr=46;
	int se=18;
	int conunt=0;
		
	while(vd>0){
                    breakk=read(fd,buffer,vd);		

      		    for(int i=0; s[i]!='\0'; i++){

                  	      if(s[i]==buffer[i]){
                        	        sr--;
                        	}   	
        	     }
			
	    	     for(int i=0; sw[i]!='\0'; i++){
				 if(sw[i]==buffer[i]){
                                         se--;
                                }
		     }	     
        	     //This Part check for massage and detrimne if is it retreve or not	
		   
		     if(sr==0){	     
              		   q=0;
			   
      	   	     }
		    
		     if(q){
                  	    for(int i=0; i<breakk; i++){
		    		  printf("%c",buffer[i]);
		    	    }
		     }
		     
		     if(se==0){
	
                          q=1;
                     }
		     vd-=breakk;
       }
       
       if(se==0){
             q=1;
       }

    
}	
void ReadAllFilePrint(int fd,char *buffer,int size){





       int x=0;
        int f=0;
        int r=size;
        int ss=1000;
	
	if(ss>size){
                ss=size;
        }
        char *buf=(char*)malloc(sizeof(char)*size);
        
        //printf("the siz %d\n",size);
        int sp=0;
        while(r>0){
                        memset(buf, '\0', size);


                        f=read(fd,buf,ss);	
                        printf("%s",buf);


                        x+=f;
                        sp++;
                        
			if(f==0 || f<0){
                                break;
                        }
                        //  printf("the siz %d\n",f);
                        r-=f;
                //      printf("%d\n",ss);
                        ss=f;

        }



	/*char *buf=buffer;
        int x=size;
        int f=0;

        while(x>0){

                f=read(fd,buf,size);
		if(buf[0]=='\0'){
			return;
		}
		if(buf[0]=='2'){
         	       return;
        	}

		if(buf[0]=='}'){
			q=0;			
		}

	

		if(q){
                	printf("%s",buf);
		}

		 if(buf[0]=='{'){
                        q=1;
                }

                if(f==0){
                        break;
                }

                buf+=f;

                x-=f;
	}
*/
	
}
void WriteAllFile(int fd,char *buffer,int size){

	char *buff=buffer;

	int x=size;
	int l=0;

	
	while(x>0){
	
		l=write(fd,buff,size);
		 
			

		if(l==0){
			break;
		}
	
		buff+=l;
	
		x-=l;
	}

	
}

void WriteExit(int fd,int flag){
	
	
//	int *x=(int*)malloc(sizeof(int));

	int x=flag;

	write(fd,&flag,sizeof(int));		

		


}

