#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

//This checks if the file are free or not
extern char *ch;
extern int *clFile;

//This funtion if user click cntorl-C
void exist(){
	int x;
	
	// if check if filed not freed than free it 
	if(ch!=NULL){
	
		free(ch);
		ch=NULL;

	}
	// if check if filed not closed than close it 
	if(clFile!=NULL){

		x=close(*clFile);
		if(x<0){
                        printf("Failed of close file\n");
                }

	}
        printf("Exiting...\n");
        exit(1);
}
