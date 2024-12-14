#include <stdio.h>
#include <dirent.h>
#include <signal.h>
#include <sys/stat.h>

char *ch;
int *clFile;

void ls(char *a);
void cat(char *a);
void exist();
void help();

//This function handle a control c and call exist function
void SIGINT_handle(int signale){

	printf("\n");
        exist();

}
//This function to take commands from main and determine each by using counters also  return number 
int paarse_cmd(char *a){

	char x[]="help";
	char y[]="ls";
	char z[]="cat";
	char c[]="exit";
	int xn=0;
	int yn=0;
        int zn=0;
	int cn=0;
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
	}else{
		return 0;
	}

}
int main(){

	char f[1024];
	int i=0;
	int s=0;	
	char file[1024];
	int r=0;
	int l=0;	
	char command[1024];
 		
        //char *buf=(char*)malloc(alocatedSize * sizeof(char));

	
	if(signal(SIGINT,SIGINT_handle)==SIG_ERR){
                perror("Faild of Caugh Signale\n");
	
        }	
	
	while(1){

	      printf(">");
              fgets(f,20,stdin);

              while(f[i]!=0){
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
	 
              i=0;
	      s=0;
	     //if for run each command by calling functions otherwise print error masage
	      if(paarse_cmd(command)==1){
			help();
	      }else if(paarse_cmd(command)==2){
			ls(file);
	      }else if(paarse_cmd(command)==3){
			cat(file);	
	      }else if(paarse_cmd(command)==4){
			exist();
	      }else{
		  printf("%s: command not found\n",command);		
	      }

	      //This Part set the command and file array to NULL

	      while(r!=-1){
              	  file[r]=0;
               	  r--;
              }
	      r=0;	

	      while(l!=-1){
                  command[l]=0;
                  l--;
              }
	      l=0;
	}
	



	return 0;
}
