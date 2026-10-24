#include <stdio.h>

int main() {
    int N_vals[] = {2, 4, 6, 8};
    double S_meas[] = {1.8, 3.4, 7.1, 8.5};
    int num_pairs = 4;

    printf("Task 15 - Estimating Serial Fraction (f) from Measurements:\n");
    printf("N\tS_meas\t\tImplied f\n");

    for(int i = 0; i < num_pairs; i++) {
        int N = N_vals[i];
        double S = S_meas[i];
        
        // Algebraic inversion formula: f = (1/S_meas - 1/N) / (1 - 1/N)
        double f = ((1.0 / S) - (1.0 / N)) / (1.0 - (1.0 / N));
        
        printf("%d\t%f\t%f\n", N, S, f);
    }

    printf("\nNote: If f is not roughly constant, the model's assumptions fail.\n");
    return 0;
}