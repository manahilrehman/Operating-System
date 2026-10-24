#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <time.h>

void* task_x(void* arg) {
    double val = 0.0;
    for(int i = 0; i < 50000000; i++) {
        val += sqrt((double)i);
    }
    return NULL;
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void* task_y(void* arg) {
    int size = 1000000;
    int *arr = (int*)malloc(size * sizeof(int));
    for(int i = 0; i < size; i++) {
        arr[i] = size - i;
    }
    qsort(arr, size, sizeof(int), compare);
    free(arr);
    return NULL;
}

int main() {
    // Version 1: Sequential execution[cite: 7]
    clock_t start_seq = clock();
    task_x(NULL);
    task_y(NULL);
    clock_t end_seq = clock();
    double t_seq = (double)(end_seq - start_seq) / CLOCKS_PER_SEC;

    // Version 2: Parallel execution using two pthreads[cite: 7]
    clock_t start_par = clock();
    pthread_t p1, p2;
    pthread_create(&p1, NULL, task_x, NULL);
    pthread_create(&p2, NULL, task_y, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    clock_t end_par = clock();
    double t_par = (double)(end_par - start_par) / CLOCKS_PER_SEC;

    printf("Task 6 - Two Independent Tasks successfully run ho gaya hai!\n");
    printf("Sequential Time (t_seq) = %f seconds\n", t_seq);
    printf("Parallel Time (t_par) = %f seconds\n", t_par);
    printf("Ratio (t_seq / t_par) = %f\n", t_seq / t_par);

    return 0;
}