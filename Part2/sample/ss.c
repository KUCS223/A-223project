#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 1024  // Buffer size for reading in chunks

// Function to read from a file and handle short reads
void read_full(int fd, char *buffer, int size) {
    int x = size;
    int bytes_read = 0;
    char *buf = buffer;
	
	printf("%d\n",*buf);

    while (x > 0) {
        bytes_read = read(fd, buf, x);  // Read from the file
        printf("%s",buf);
       
        if (bytes_read == 0) {
            break;
        }

        buf += bytes_read;       // Move buffer pointer forward
        x -= bytes_read;  // Decrease the number of bytes left to read
    }

    //return (size - bytes_left);  // Return the number of bytes actually read
}

int main() {
    const char *filename = "main.c";  // File to read
    int fd = open(filename, O_RDONLY); // Open the file for reading

    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Allocate memory for the content to be read
    int file_size = 4096;  // Set this to the desired size to read (or dynamically determine file size)
    char *buffer =((char*) malloc(file_size));

   
    // Read the file fully into the buffer
     read_full(fd, buffer, file_size);

   

    return 0;
}

