#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "file_operations.h"

int create_and_write_file(const char *filename, const char *content) {
    int fd;                         // File descriptor
    ssize_t bytes_written;          // Number of bytes written

    printf("Creating file: %s\n", filename);
    printf("Writing content: %s\n", content);

    // Open the file with flags: create if not exists, write-only, truncate existing
    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return -1;
    }

    printf("File descriptor: %d\n", fd);

    // Write content to the file
    bytes_written = write(fd, content, strlen(content));
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return -1;
    }

    printf("Successfully wrote %zd bytes to %s\n", bytes_written, filename);

    // Close the file
    if (close(fd) == -1) {
        perror("Error closing file");
        return -1;
    }

    printf("File %s closed successfully.\n", filename);
    return 0;
}

int read_file_contents(const char *filename) {
    int fd;                         // File descriptor
    char buffer[1024];              // Buffer to read contents
    ssize_t bytes_read;             // Number of bytes read

    printf("Reading file: %s\n", filename);

    // Open the file for reading
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for reading");
        return -1;
    }

    printf("File descriptor: %d\n", fd);
    printf("File contents:\n--------------------\n");

    // Read in a loop
    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';  // Null-terminate buffer
        printf("%s", buffer);
    }

    if (bytes_read == -1) {
        perror("Error reading file");
        close(fd);
        return -1;
    }

    printf("\n--------------------\nEnd of file.\n");

    // Close the file
    if (close(fd) == -1) {
        perror("Error closing file");
        return -1;
    }

    printf("File %s closed successfully.\n", filename);
    return 0;
}

