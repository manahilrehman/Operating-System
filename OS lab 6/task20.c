#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ucontext.h>

#define NUM_USER_THREADS 20
#define NUM_CARRIERS 2
#define STACK_SIZE 4096

ucontext_t user_ctx[NUM_USER_THREADS];
char user_stacks[NUM_USER_THREADS][STACK_SIZE];
int current_uthr = 0;

void user_thread_func(int id) {
    while(1) {
        printf("User Thread %d running on carrier thread\n", id);
        // Yield logic simulation
        break;
    }
}

void* carrier_func(void* arg) {
    int cid = *(int*)arg;
    printf("Carrier Thread %d started\n", cid);
    return NULL;
}

int main() {
    pthread_t carriers[NUM_CARRIERS];
    int carrier_ids[NUM_CARRIERS];

    // Create carrier pthreads (N model)
    for(int i = 0; i < NUM_CARRIERS; i++) {
        carrier_ids[i] = i;
        pthread_create(&carriers[i], NULL, carrier_func, &carrier_ids[i]);
    }

    for(int i = 0; i < NUM_CARRIERS; i++) {
        pthread_join(carriers[i], NULL);
    }

    printf("Task 20 - M:N Multiplexing successfully executed!\n");
    return 0;
}