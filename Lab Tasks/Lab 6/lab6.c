#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    int pipe1[2];
    int pipe2[2];
    pid_t pid;
    char parent_msg[] = "Message";
    char child_msg[] = "Reply";
    char buf[100];

    if (pipe(pipe1) == -1)
    {
        printf("Error creating pipe1\n");
        exit(1);
    }

    if (pipe(pipe2) == -1)
    {
        printf("Error creating pipe2\n");
        exit(2);
    }

    pid = fork();

    if (pid == -1)
    {
        printf("Error creating process\n");
        exit(3);
    }

    if (pid == 0) // Child process
    {
        close(pipe1[1]); // Close write end of pipe1
        close(pipe2[0]); // Close read end of pipe2
        
        sleep(1); // sleep so parent writes first
        
        for (int i = 0; i < 3; i++)
        {
            ssize_t bytesRead = read(pipe1[0], buf, sizeof(buf) - 1);
            if (bytesRead <= 0)
            {
                printf("Error reading from pipe1\n");
                exit(4);
            }
            buf[bytesRead] = '\0';
            printf("Child received: %s %d\n", buf, i + 1);
        }
         
        for (int i = 0; i < 3; i++)
        {
            ssize_t bytesWritten = write(pipe2[1], child_msg, strlen(child_msg) + 1);
            if (bytesWritten == -1)
            {
                printf("Error writing to pipe2\n");
                exit(5);
            }
        }

        close(pipe1[0]); // Close read end of pipe1
        close(pipe2[1]); // Close write end of pipe2
        exit(0);
    }
    else // Parent process
    {
        close(pipe1[0]); // Close read end of pipe1
        close(pipe2[1]); // Close write end of pipe2
        
        for (int i = 0; i < 3; i++)
        {
            ssize_t bytesWritten = write(pipe1[1], parent_msg, strlen(parent_msg) + 1);
            if (bytesWritten == -1)
            {
                printf("Error writing to pipe1\n");
                exit(6);
            }
        }

        sleep(3);

        for (int i = 0; i < 3; i++)
        {
            ssize_t bytesRead = read(pipe2[0], buf, sizeof(buf) - 1);
            if (bytesRead <= 0)
            {
                printf("Error reading from pipe2\n");
                exit(7);
            }
            buf[bytesRead] = '\0';
            printf("Parent received: %s %d\n", buf, i + 1);
        }
        
        close(pipe1[1]); // Close write end of pipe1
        close(pipe2[0]); // Close read end of pipe2
        wait(NULL); // Wait for child process to finish
        exit(0);
    }
}

