#include <unistd.h>
#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <limits.h>

sem_t semaphore;
int MIN_VALUE = INT_MAX; 

typedef struct 
{
    int arr[15];
    int startPoint;
    int endPoint;
} array;

void* summation(void * args)
{
    array* temp = (array*) args;
    sem_wait(&semaphore);
    
    for (int i = temp->startPoint; i <= temp->endPoint; i++)
    {
        if (temp->arr[i] < MIN_VALUE)
        {
            MIN_VALUE = temp->arr[i];
        }
    }

    sem_post(&semaphore);
    return NULL;
}

int main()
{
    array a1, a2, a3;
    for (int i = 0; i < 15; i++)
    {
        a1.arr[i] = a2.arr[i] = a3.arr[i] = i + 1;
    }

    a1.startPoint = 0;   a1.endPoint = 4;
    a2.startPoint = 5;   a2.endPoint = 9;
    a3.startPoint = 10;  a3.endPoint = 14;

    pthread_t t1, t2, t3;

    sem_init(&semaphore, 0, 1);

    pthread_create(&t1, NULL, summation, (void*)&a1);
    pthread_create(&t2, NULL, summation, (void*)&a2);
    pthread_create(&t3, NULL, summation, (void*)&a3);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("The MIN VALUE of the array is: %d\n", MIN_VALUE);

    sem_destroy(&semaphore);
    return 0;
}
