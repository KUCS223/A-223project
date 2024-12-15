#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

void ReadAllFilePrint(char *buffer, int size) {
    // Print exactly `size` bytes from the buffer
    printf("%.*s", size, buffer);
}

void Read(int fd, char *buffer, int size) {
    int chunk_size = 10;  // Read in chunks of 10 bytes
    char *buf = buffer;
    int bytes_read = 0;
    int f = 0;

    // Read the file in chunks of size `chunk_size`
    while (bytes_read < size) {
        // Read data into the buffer
        f = read(fd, buf, chunk_size);

        if (f == 0) {
            break;  // End of file reached
        } else if (f < 0) {
            perror("read");
            break;
        }

        // Print the content read from the file
        ReadAllFilePrint(buf, f);

        // Move the buffer pointer forward by the number of bytes read
        buf += f;
        bytes_read += f;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "U#isage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat fileStat;

    // Get file size
    if (stat(argv[1], &fileStat) != 0) {
        perror("stat");
        return 1;
    }

    // Get file size
    int allocatedSize = fileStat.st_size;
    if (allocatedSize == 0) {
        printf("File is empty.\n");
        return 0;
    }

    // Allocate buffer to hold file content
    char *buf = (char *)malloc(allocatedSize * sizeof(char));
    if (buf == NULL) {
        perror("malloc");
        return 1;
    }

    // Open the file for reading
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        free(buf);
        return 1;
    }

    // Read the file in chunks and print
    Read(fd, buf, allocatedSize);

    // Clean up
    close(fd);
    free(buf);

    return 0;
}

          ��                                                                                                                                                             