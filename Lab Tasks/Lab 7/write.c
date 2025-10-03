#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

//PIPE NAME
#define PIPE "/tmp/my_pipe"

int main() 
{ 
    int fd;
    char message[] = "Hello from producer 1";

    // Open the FIFO for writing
    fd = open(PIPE, O_WRONLY);
    if (fd == -1) 
    {
        perror("Error opening FIFO for writing");
        exit(EXIT_FAILURE);
    }

    // Try to write without blocking
    if (write(fd, message, strlen(message) + 1) == -1) 
    {
        perror("Error writing to FIFO (No reader present)");
    } 
    else 
    {
        printf("Message sent: %s\n", message);
    }

    close(fd);
    return 0;
}

