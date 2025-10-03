#include <stdio.h>
#include <pthread.h>


void * threadInfo (void * args)
{
	//cast as struct
	pthread_attr_t * attr = (pthread_attr_t *)args;

	printf("The Thread ID is : %zu\n",pthread_self());

	//Print other Attrs
	size_t stackSize;
	int policy;

	pthread_attr_getstacksize(attr,&stackSize);
	pthread_attr_getschedpolicy(attr,&policy);

	printf("Stack Size: %zu\n",stackSize);

	printf("Scheduling policy: ");
    switch (policy)
    {
        case SCHED_FIFO:    printf("SCHED_FIFO\n"); break;
        case SCHED_RR:      printf("SCHED_RR\n"); break;
        case SCHED_OTHER:   printf("SCHED_OTHER (default)\n"); break;
        default:            printf("Unknown\n"); break;
    }
		return NULL;

}
int main()
{
	//initialize thread
	pthread_t t1;

	//create attr struct
	pthread_attr_t t1_attr;

	//initialize struct obj
	pthread_attr_init(&t1_attr);

	//set stack size as 3 mb
	pthread_attr_setstacksize(&t1_attr,3*1024*1024);

	//set schedule policy as FIFO
	pthread_attr_setschedpolicy(&t1_attr,SCHED_FIFO);

	//set thread as join
	pthread_attr_setdetachstate(&t1_attr,PTHREAD_CREATE_JOINABLE);

	// create thread
	pthread_create(&t1,&t1_attr,threadInfo,&t1_attr);
	
	//wait for thread to finish
	pthread_join(t1,NULL);

	//Free up struct space
	pthread_attr_destroy(&t1_attr);

	return 0;
}

