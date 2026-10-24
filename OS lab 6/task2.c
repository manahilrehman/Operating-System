#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main() {
    int n = 1000;
    float *A = (float*) malloc(n * sizeof(float));
    float *B = (float*) malloc(n * sizeof(float));
    float *C = (float*) malloc(n * sizeof(float));

    // Arrays ko initialize karna
    for(int i = 0; i < n; i++) {
        A[i] = i * 1.0f;
        B[i] = 2.0f;
    }

    // OpenMP parallel loop for Task 2 vector expression
    #pragma omp parallel for
    for(int i = 0; i < n; i++) {
        C[i] = A[i] * B[i] + sin(A[i]);
    }

    printf("Parallel vector expression successfully run ho gaya hai! n = %d\n", n);
    printf("Sample result C[10] = %f\n", C[10]);

    free(A);
    free(B);
    free(C);
    return 0;
}