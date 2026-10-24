#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void busy(int ms) {
    clock_t start = clock();
    while ((double)(clock() - start) / CLOCKS_PER_SEC * 1000.0 < ms);
}

typedef struct {
    int ms;
} ThreadArgs;

void* thread_func(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    busy(args->ms);
    return NULL;
}

void run_phase(int workloads[], const char* name) {
    pthread_t threads[4];
    ThreadArgs args[4];

    clock_t t0 = clock();

    for (int i = 0; i < 4; i++) {
        args[i].ms = workloads[i];
        pthread_create(&threads[i], NULL, thread_func, &args[i]);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_t now = clock();
    double elapsed = (double)(now - t0) / CLOCKS_PER_SEC * 1000.0;
    printf("%s Wall Time = %f ms\n", name, elapsed);
}

int main() {
    int unbalanced[4] = {100, 400, 100, 400};
    int balanced[4] = {250, 250, 250, 250};

    printf("Task 9 - Fork-Join Load Imbalance Demo:\n");
    run_phase(unbalanced, "Unbalanced Workload (t_imbal)");
    run_phase(balanced, "Balanced Workload (t_bal)");

    return 0;
}