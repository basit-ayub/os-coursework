#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <stdbool.h>


int main()
{
	
	char * newVars[]={"MY_VAR=HELLO WORLD",NULL};
	
	execle("/usr/bin/env","env",NULL,newVars);
	
}
