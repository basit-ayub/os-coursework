#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
    pid_t child1 = fork();

    if (child1 == 0)  // first child
    {
        pid_t child3 = fork();
        if (child3 == 0)
        {
            pid_t child7 = fork();
            if (child7 == 0)
            {
                printf("H\n"); // child7 print
            }
            else
            {
                printf("D\n"); // child3 print
            }
        }
        else
        {
            pid_t child6 = fork();
            if (child6 == 0)
            {
                printf("G\n"); // child6 print
            }
            else
            {
                printf("B\n"); // child1 print
            }
        }
    }
    else
    {
        pid_t child2 = fork();
        if (child2 == 0)
        {
            pid_t child5 = fork();
            if (child5 == 0)
            {
                printf("F\n"); // child5 print
            }
            else
            {
                printf("C\n"); // child2 print
            }
        }
        else
        {
            pid_t child4 = fork();
            if (child4 == 0)
            {
                printf("E\n"); // child4 prints E
            }
            else
            {
                printf("A\n"); // Parent Print
            }
        }
    }
    return 0;
}

