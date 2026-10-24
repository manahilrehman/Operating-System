#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n = 1000;
    float *A = (float*) malloc(n * sizeof(float));
    float total_sum = 0.0f;

    // Array ko initialize karna
    for(int i = 0; i < n; i++) {
        A[i] = 1.0f; // As an example sab elements ko 1.0 rakh diya hai
    }

    // Task 1: Parallel Array Sum (OpenMP reduction ke sath)
    #pragma omp parallel for reduction(+:total_sum)
    for(int i = 0; i < n; i++) {
        total_sum += A[i];
    }

    printf("Task 1 - Chunked Parallel Array Sum successfully run ho gaya hai!\n");
    printf("Total Sum = %f\n", total_sum);

    free(A);
    return 0;
}