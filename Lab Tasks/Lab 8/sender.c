#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


void sigchld_handler(int sig) 
{
    int status;
    pid_t pid;

    pid = wait(&status);
    if (pid > 0) 
    {
        printf("Child process %d terminated with status %d\n", pid, WEXITSTATUS(status));
    }
}

int main() 
{
    signal(SIGCHLD, sigchld_handler);

    pid_t pid = fork();

    if (pid == 0) 
    {
      
        printf("Child process (PID: %d) is running...\n", getpid());
        sleep(1);
        printf("Child process (PID: %d) is exiting...\n", getpid());
        exit(0); 
    } 
    else if (pid > 0) 
    {
        
        printf("Parent process (PID: %d) is waiting for the child...\n", getpid());
        while (1) 
        {
            sleep(1);
        }
    } 

    return 0;
}

