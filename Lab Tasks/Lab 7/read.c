#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// PIPE NAME
#define PIPE "/tmp/my_pipe"

int main() 
{ 
    int fd; 
    char buffer[100];

    // Open the FIFO for reading (Blocking mode so it waits for writers)
    fd = open(PIPE, O_RDONLY);
    if (fd == -1) 
    { 
        perror("Error opening FIFO");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for data...\n");

    while (1) 
    {
        int x = read(fd, buffer, sizeof(buffer) - 1); 
        
        if (x > 0) 
        {
            buffer[x] = '\0'; 
            printf(" %s\n", buffer);
        } 
        else if (x == 0) 
        {
            sleep(3); 
        else 
        {
            perror("Error reading from FIFO");
            break;
        }
    }

    close(fd);
    return 0;
}

