#include <stdio.h>
#include <pthread.h>

void * func1(void * arg)
{
	pthread_t t= pthread_self();
	printf("Hello from Thread ID :%lu\n",t);
	return NULL;
}
void * func2(void * arg)
{
	pthread_t t= pthread_self();
	printf("Hello from Thread ID :%lu\n",t);
	return NULL;
}
void * func3(void * arg)
{
	pthread_t t= pthread_self();
	printf("Hello from Thread ID :%lu\n",t);
	return NULL;
}
void * func4(void * arg)
{
	pthread_t t= pthread_self();
	printf("Hello from Thread ID :%lu\n",t);
	return NULL;
}
void * func5(void * arg)
{
	pthread_t t= pthread_self();
	printf("Hello from Thread ID :%lu\n",t);
	return NULL;
}

int main()
{
	pthread_t t1;
	pthread_create(&t1,NULL,func1,NULL);
	
	pthread_t t2;
	pthread_create(&t2,NULL,func1,NULL);
	
	pthread_t t3;
	pthread_create(&t3,NULL,func1,NULL);
	
	pthread_t t4;
	pthread_create(&t4,NULL,func1,NULL);
	
	pthread_t t5;
	pthread_create(&t5,NULL,func1,NULL);
	
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
	pthread_join(t4,NULL);
	pthread_join(t5,NULL);
	

	return 0;
}

