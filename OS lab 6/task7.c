#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define K 5 // Buffer size

int B[K];
int in = 0, out = 0, count = 0;

pthread_mutex_t m;
pthread_cond_t notFull;
pthread_cond_t notEmpty;

void* producer(void* arg) {
    for(int i = 0; i < 10; i++) {
        pthread_mutex_lock(&m);
        while(count == K) {
            pthread_cond_wait(&notFull, &m);
        }
        B[in] = i;
        in = (in + 1) % K;
        count++;
        printf("Produced: %d\n", i);
        pthread_cond_signal(&notEmpty);
        pthread_mutex_unlock(&m);
    }
    // Push sentinel -1 to stop consumer[cite: 8]
    pthread_mutex_lock(&m);
    while(count == K) {
        pthread_cond_wait(&notFull, &m);
    }
    B[in] = -1;
    in = (in + 1) % K;
    count++;
    pthread_cond_signal(&notEmpty);
    pthread_mutex_unlock(&m);
    return NULL;
}

void* consumer(void* arg) {
    while(1) {
        pthread_mutex_lock(&m);
        while(count == 0) {
            pthread_cond_wait(&notEmpty, &m);
        }
        int x = B[out];
        out = (out + 1) % K;
        count--;
        pthread_cond_signal(&notFull);
        pthread_mutex_unlock(&m);

        if(x == -1) break;
        printf("Consumed: %d\n", x);
    }
    return NULL;
}

int main() {
    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&notFull, NULL);
    pthread_cond_init(&notEmpty, NULL);

    pthread_t prod, cons;
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&notFull);
    pthread_cond_destroy(&notEmpty);

    printf("Task 7 - Producer-Consumer successfully run ho gaya hai!\n");
    return 0;
}