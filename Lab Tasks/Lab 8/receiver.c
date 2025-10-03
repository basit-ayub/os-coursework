#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigusr_handler(int sig) 
{
    if (sig == SIGUSR1) 
    {
        printf("Received SIGUSR1!\n");
        
    } 
    else if (sig == SIGUSR2) 
    {
        printf("Received SIGUSR2!\n");
    }
    
    printf("Exiting...");
    exit(0);
    
}

int main() 
{
    signal(SIGUSR1, sigusr_handler);
    signal(SIGUSR2, sigusr_handler);

      printf("Waiting for SIGUSR1 or SIGUSR2...\n");
      pause();
    

    return 0;
}

