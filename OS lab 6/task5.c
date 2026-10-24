#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n = 1000;
    float *A = (float*) malloc(n * sizeof(float));
    float *B = (float*) malloc(n * sizeof(float));
    for(int i = 0; i < n; i++) {
        A[i] = 1.0f;
        B[i] = 2.0f;
    }

    float dot = 0.0f;

    #pragma omp parallel for reduction(+:dot)
    for(int i = 0; i < n; i++) {
        dot += A[i] * B[i];
    }

    printf("Task 5 - Dot Product successfully run ho gaya hai!\n");
    printf("Dot Product Result = %f\n", dot);

    free(A);
    free(B);
    return 0;
}