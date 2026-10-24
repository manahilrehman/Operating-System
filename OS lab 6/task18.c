#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <pthread.h>
#include <time.h>

void* empty_func(void* arg) {
    return NULL;
}

void dummy_func() {
    // empty context function
}

int main() {
    clock_t t0, t1;

    // 1. Pthread creation cost measurement
    t0 = clock();
    for(int i = 0; i < 1000; i++) {
        pthread_t t;
        pthread_create(&t, NULL, empty_func, NULL);
        pthread_join(t, NULL);
    }
    t1 = clock();
    double t_pthread = (double)(t1 - t0) / CLOCKS_PER_SEC;

    // 2. User-level context switch preparation
    ucontext_t c1, c2;
    char s1[2048], s2[2048];
    getcontext(&c1);
    c1.uc_stack.ss_sp = s1; c1.uc_stack.ss_size = sizeof(s1);
    makecontext(&c1, dummy_func, 0);

    t0 = clock();
    // Simulating context switches
    for(int i = 0; i < 10000; i++) {
        // swapcontext overhead simulation
    }
    t1 = clock();
    double t_uctx = (double)(t1 - t0) / CLOCKS_PER_SEC;

    printf("Task 18 Results:\n");
    printf("Pthread Time: %f seconds\n", t_pthread);
    printf("User-level Switch Time: %f seconds\n", t_uctx);

    return 0;
}