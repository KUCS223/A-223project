#include <stdio.h>


//This function print help menu
void help(){

    printf("help: print a help menu\n");
        printf("ls: list files in current remote directory\n");
        printf("ls *.txt: list text files\n");
        printf("cat: output file contents\n");
        printf("ret filename: retrieve filename\n");
        printf("ret *.txt: retrieve all text files\n");
	printf("stat: print statistics\n");
	printf("exit: exit the file server\n");
}
