#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>


//Function that return the size of string array 
int size(char *p){

        int sizeS=0;
        while(*p!='\0'){
                sizeS++;
                p++;
        }
        return sizeS;
}

//This funtion check if there is wildcard or not 
int wildcardCheck(char *file){

        int x=0;
        for(int i=0; file[i]!=0; i++){
                if(file[i]==42 && file[i+1]==0){
                        x=3;
                }
        }
        for(int i=0; file[i]!=0; i++){
                if(file[i]==42){
                       if(file[i+1]!=0 && file[i-1]!=0){
                         x=2;
                       }
                }
        }
	//Return 1 if wildcard at begaining of string 
        if(file[0]==42){
                return 1;
	//Return 2 if wildcard at mid of string 
        }else if(x==2){

                return 2;
	//Return 3 if wildcard at last of string 
        }else if(x==3){

                return 3;
	//Return 0 if there is no wildcard
        }else {

                return 0;
 	}
}

//This function check of last charcter in string if equal or not for cat command 
int lastwordcheckCat(char *a,char *u){
        int Aindex=0;
        int Uindex=0;

        for(int i=0; u[i]!=0; i++){
                Uindex=i;
        }
        for(int i=1; a[i]!=0; i++){
                Aindex=i;
        }


        if(a[Aindex]==u[Uindex]){
                return 1;
        }else{
                return 0;
        }

}

//Function check if word is match or not for cat command  
int matchWord(char *a,char *u,int t){
        int sizeA=size(a);
        int x=0;
        for(int j=0; j<sizeA; j++){
                        if(a[j]==u[j]){
                                 x+=1;
                        }
        }

        if(x==size(u)-1){
                return 1;
        }else{
                return 0;
        }
}


//This function check of last charcter in string if equal or not for ls command 
int lastwordcheck(char *a,char *u){

        int Aindex=0;
        int Uindex=0;


        for(int i=0; u[i+1]!=0; i++){
                Uindex=i;
        }
        for(int i=1; a[i]!=0; i++){
                Aindex=i;
        }


        if(a[Aindex]==u[Uindex]){
                return 1;
        }else{
                return 0;
        }


}
//Function check if word is match or not for ls command
int matchWordLS(char *a,char *u,int t){

        int sizeA=size(a);
        int sizeB=0;
        int x=0;

                for(int j=0; j<size(u); j++){
                         if(a[j]==u[j]){
                               x+=1;
                         }
                }
        if(x==size(u)-2){
                return 1;
        }else{
                return 0;
        }


}

//This function for wildcard in middle that return 1 if mach of the word in current derectory otherwise return 0;
int checkstr(char *a,char *p,int s){

        int sizx=size(a)-1;
        int i=0;
        int r=0;
        while(a[i]!=42){

                if(p[i]==a[i]){
                        r++;
                }

                i++;
        }
        i++;
        char *t;
        int j=i;
        while(a[i]!='\0'){
                while(p[j]!='\0'){
                        t=p;
                        if(a[i]==p[j]){
                                i++;
                                r++;
                        }
                        j++;
                }
                i++;
        }
                if(r==sizx){
                            return 1;

                }else{
                        return 0;
                }
}
