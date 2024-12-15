#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int q=1;
int count=0;
void decrypt(char *encrypted, char *original,int size){

	for(int i=0; i<size; i++){
        	  original[i]=encrypted[i]-5;
        }
}
char *ReadAllFile(int fd,char *buffer,int size){

        int breakk;
        int vd=size;
        char *s="This is retrevie function shutdown printf 2232";
        char *sw="Start again printf";
        int flag;
        buffer=(char*)malloc(vd*sizeof(char));
        char *pt;
        int sr=46;
        int se=18;
        int conunt=0;
        int ui=0;
	char *r;
	r=(char*)malloc(vd*sizeof(char));

        while(vd>0){
                    breakk=read(fd,buffer,vd);

		    decrypt(buffer,r,size);


                    for(int i=0; s[i]!='\0'; i++){
                              if(s[i]==r[i]){
                                        sr--;
                                }
                     }

                     for(int i=0; sw[i]!='\0'; i++){
			     if(sw[i]==r[i]){
                                         se--;
                                }
                     }
                     //This Part check for massage and detrimne if is it retreve or not
                     if(sr==0){
                           q=0;

                     }

                     if(q){
                            for(int i=0; i<breakk; i++){
                                  printf("%c",r[i]);
                            }
                     }

                     if(se==0){
                          q=1;
                     }
                     vd-=breakk;
       }
         se=18;
         sr=46;
       return r;
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
        int x=flag;
        write(fd,&flag,sizeof(int));
}
