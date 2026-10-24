#include <stdio.h>

int main() {
    double p = 0.90; // Measured parallel fraction
    double measured_S[] = {1.0, 1.8, 3.4, 6.2, 7.1, 7.8, 8.2, 8.5}; 

    printf("Task 14 - Amdahl vs. Gustafson (p = %.2f):\n", p);
    printf("N\tS_Amdahl\tS_Gustafson\tMeasured S(N)\n");

    for (int N = 1; N <= 8; N++) {
        double s_amdahl = 1.0 / ((1.0 - p) + (p / N));
        double s_gustafson = N - (1.0 - p) * (N - 1);
        printf("%d\t%f\t%f\t%f\n", N, s_amdahl, s_gustafson, measured_S[N-1]);
    }

    return 0;
}