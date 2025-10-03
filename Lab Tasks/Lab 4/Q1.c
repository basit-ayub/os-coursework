#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
	
	for(int i=0;i<3;i++)
	{
		pid_t temp=fork();
		int sum=1+2+3+4+5;
		if(temp==0)
		{
		printf("Child %d : PID= %d , PPID= %d\n",i+1,getpid(),getppid());
		printf("Child %d Task Completed Sum is  = %d\n",i+1,sum);
		exit(1);
		}
		else
		{
		sleep(1);
		printf("Parent : Child %d (PID:%d) has Completed!\n",i+1,getpid());
		}
		
	}
	printf("All children are terminated!\n");
	
	return 0;
}

