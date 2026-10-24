#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>

void* worker(void* arg) {
    long tid = syscall(SYS_gettid);
    printf("Worker Thread -> PID: %d, TID: %ld\n", getpid(), tid);
    sleep(30); // Sleep to inspect via /proc
    return NULL;
}

int main() {
    printf("Main Process PID: %d\n", getpid());
    pthread_t threads[4];

    for(int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, worker, NULL);
    }

    for(int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}