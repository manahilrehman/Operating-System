#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

void task_x() {
    double val = 0.0;
    for(int i = 0; i < 50000000; i++) {
        val += sqrt((double)i);
    }
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void task_y() {
    int size = 1000000;
    int *arr = (int*)malloc(size * sizeof(int));
    for(int i = 0; i < size; i++) {
        arr[i] = size - i;
    }
    qsort(arr, size, sizeof(int), compare);
    free(arr);
}

int main() {
    double t0 = omp_get_wtime();

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            task_x();
        }
        #pragma omp section
        {
            task_y();
        }
    }

    double t1 = omp_get_wtime();
    printf("Task 10 - OpenMP Sections successfully run ho gaya hai!\n");
    printf("Execution Time = %f seconds\n", t1 - t0);

    return 0;
}