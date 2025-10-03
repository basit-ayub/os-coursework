#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main() 
{
int pipe1[2];
	if(pipe(pipe1)==-1)
		printf("Error in pipe");
		
int parent = fork();

if(parent==0)
{	
	
	close(pipe1[0]);
	dup2(pipe1[1],1);
	printf("This is message from child to Parent using printf");
	close(pipe1[1]);

}
else
{
	sleep(1);
	close(pipe1[1]);
	char buf[100];
	ssize_t bytesRead = read(pipe1[0], buf, sizeof(buf) - 1);
	buf[bytesRead] = '\0';
	printf("%s",buf);
}

}

