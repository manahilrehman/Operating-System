#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 128

int main() {
    float **A = (float**)malloc(N * sizeof(float*));
    float **B = (float**)malloc(N * sizeof(float*));
    float **C = (float**)malloc(N * sizeof(float*));

    for(int i = 0; i < N; i++) {
        A[i] = (float*)malloc(N * sizeof(float));
        B[i] = (float*)malloc(N * sizeof(float));
        C[i] = (float*)malloc(N * sizeof(float));
        for(int j = 0; j < N; j++) {
            A[i][j] = 1.0f;
            B[i][j] = 1.0f;
            C[i][j] = 0.0f;
        }
    }

    #pragma omp parallel for collapse(2)
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            float s = 0.0f;
            for(int k = 0; k < N; k++) {
                s += A[i][k] * B[k][j];
            }
            C[i][j] = s;
        }
    }

    printf("Task 3 - Matrix Multiplication successfully run ho gaya hai!\n");
    printf("Sample C[0][0] = %f\n", C[0][0]);

    for(int i = 0; i < N; i++) {
        free(A[i]); free(B[i]); free(C[i]);
    }
    free(A); free(B); free(C);
    return 0;
}