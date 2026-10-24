#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n = 1000;
    float *A = (float*) malloc(n * sizeof(float));
    for(int i = 0; i < n; i++) {
        A[i] = (float)(i * 1.5);
    }
    A[500] = 9999.0f; // Max element

    float max_val = A[0];

    #pragma omp parallel for reduction(max:max_val)
    for(int i = 0; i < n; i++) {
        if(A[i] > max_val) {
            max_val = A[i];
        }
    }

    printf("Task 4 - Parallel Maximum successfully run ho gaya hai!\n");
    printf("Maximum Element = %f\n", max_val);

    free(A);
    return 0;
}