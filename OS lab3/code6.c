#include <stdio.h>
#include <windows.h>

#define SIZE 3

int matrix[SIZE][SIZE] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};
int vector[SIZE] = {1, 2, 3};
int result[SIZE];

// Thread argument structure
typedef struct {
    int row_idx;
} ThreadData;

// Worker function for matrix-vector row multiplication
DWORD WINAPI worker_multiply_row(LPVOID arg) {
    ThreadData *data = (ThreadData *)arg;
    int row = data->row_idx;
    int sum = 0;

    for (int col = 0; col < SIZE; col++) {
        sum += matrix[row][col] * vector[col];
    }
    result[row] = sum;

    return 0;
}

int main() {
    HANDLE threads[SIZE];
    ThreadData thread_data[SIZE];

    // Spawn 3 threads for rows 0 to 2
    for (int i = 0; i < SIZE; i++) {
        thread_data[i].row_idx = i;
        threads[i] = CreateThread(
            NULL, 0, worker_multiply_row, &thread_data[i], 0, NULL
        );
    }

    // Wait for all threads to complete (JOIN)
    WaitForMultipleObjects(SIZE, threads, TRUE, INFINITE);

    // Close thread handles
    for (int i = 0; i < SIZE; i++) {
        CloseHandle(threads[i]);
    }

    // Print output
    printf("Result Vector: [%d, %d, %d]\n", result[0], result[1], result[2]);

    return 0;
}