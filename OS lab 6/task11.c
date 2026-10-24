#include <stdio.h>

int main() {
    double p = 0.90; // Parallel fraction (e.g., 90%)
    int N_max = 16;

    printf("Task 11 - Amdahl's Law Theoretical Speedup (p = %.2f):\n", p);
    printf("N\tSpeedup S(N)\n");

    for (int N = 1; N <= N_max; N++) {
        double S = 1.0 / ((1.0 - p) + (p / N));
        printf("%d\t%f\n", N, S);
    }

    return 0;
}