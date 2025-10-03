#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int balanceA = 1000;
int balanceB = 1000;

pthread_mutex_t lockA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lockB = PTHREAD_MUTEX_INITIALIZER;

void* transferAtoB(void* arg) {
    while (pthread_mutex_trylock(&lockA)) {
        sleep(1);
    }

    printf("A->B: Locked A\n");
    sleep(1);

    while (pthread_mutex_trylock(&lockB)) {
        sleep(1);
    }

    printf("A->B: Locked B\n");

    balanceA -= 100;
    balanceB += 100;

    pthread_mutex_unlock(&lockB);
    pthread_mutex_unlock(&lockA);

    return NULL;
}

void* transferBtoA(void* arg) {
    pthread_mutex_trylock(&lockA);

    printf("B->A: Locked A\n");
    sleep(1);

    pthread_mutex_trylock(&lockB);

    printf("B->A: Locked B\n");

    balanceB -= 50;
    balanceA += 50;

    pthread_mutex_unlock(&lockA);
    pthread_mutex_unlock(&lockB);

    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, transferAtoB, NULL);
    pthread_create(&t2, NULL, transferBtoA, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final balances: A = %d, B = %d\n", balanceA, balanceB);

    return 0;
}

