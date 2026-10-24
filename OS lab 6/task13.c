#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n = 20000000;
    float *A = (float*)malloc(n * sizeof(float));
    for(int i = 0; i < n; i++) A[i] = 1.0f;

    double T1 = 0.0;

    printf("Task 13 - Strong Scaling Experiment:\n");
    printf("T\tTime (s)\tSpeedup S(T)\tEfficiency E(T)\n");

    for(int T = 1; T <= 8; T++) {
        double sum = 0;
        double start = omp_get_wtime();

        #pragma omp parallel for reduction(+:sum) num_threads(T)
        for(int i = 0; i < n; i++) {
            sum += A[i];
        }

        double end = omp_get_wtime();
        double t_T = end - start;

        if(T == 1) {
            T1 = t_T;
        }

        double S_T = T1 / t_T;
        double E_T = S_T / T;

        printf("%d\t%f\t%f\t%f\n", T, t_T, S_T, E_T);
    }

    free(A);
    return 0;
}