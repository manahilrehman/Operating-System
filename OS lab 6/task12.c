#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main() {
    int n = 10000000;
    float *A = (float*)malloc(n * sizeof(float));
    for(int i = 0; i < n; i++) A[i] = 1.0f;

    double f = 0.10; // Chosen serial fraction
    int n_ser = (int)(f * n);

    // 1. Measure fully sequential sum time (T_seq)
    clock_t t_start = clock();
    float total_seq = 0;
    for(int i = 0; i < n; i++) total_seq += A[i];
    clock_t t_end = clock();
    double T_seq = (double)(t_end - t_start) / CLOCKS_PER_SEC;

    int threads[] = {1, 2, 4, 8};
    printf("Task 12 - Measured vs Predicted Speedup (f = %.2f):\n", f);
    printf("T\tMeasured Speedup\tPredicted Speedup\n");

    for(int idx = 0; idx < 4; idx++) {
        int T = threads[idx];

        double start_time = omp_get_wtime();

        // Serial section on main thread[cite: 11]
        float s_ser = 0;
        #pragma omp parallel for reduction(+:s_ser) num_threads(1)
        for(int i = 0; i < n_ser; i++) {
            s_ser += A[i];
        }

        // Chunked parallel sum of remaining elements[cite: 11]
        float s_par = 0;
        #pragma omp parallel for reduction(+:s_par) num_threads(T)
        for(int i = n_ser; i < n; i++) {
            s_par += A[i];
        }

        double end_time = omp_get_wtime();
        double t_T = end_time - start_time;

        double measured_speedup = (t_T > 0) ? (T_seq / t_T) : 0;
        double predicted_speedup = 1.0 / (f + (1.0 - f) / T);

        printf("%d\t%f\t\t%f\n", T, measured_speedup, predicted_speedup);
    }

    free(A);
    return 0;
}