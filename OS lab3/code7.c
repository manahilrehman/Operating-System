#include <stdio.h>
#include <windows.h>

int counter = 0; // GLOBAL counter = 0

// Thread function to increment counter 100,000 times
DWORD WINAPI increment_task(LPVOID arg) {
    for (int i = 0; i < 100000; i++) {
        counter = counter + 1; // Unsynchronized read-modify-write
    }
    return 0;
}

int main() {
    HANDLE thread1, thread2;

    // SPAWN thread1 and thread2
    thread1 = CreateThread(NULL, 0, increment_task, NULL, 0, NULL);
    thread2 = CreateThread(NULL, 0, increment_task, NULL, 0, NULL);

    // JOIN thread1 and thread2
    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);

    // Close thread handles
    CloseHandle(thread1);
    CloseHandle(thread2);

    // Print final counter value showing race condition
    printf("Expected: 200000 | Actual counter: %d\n", counter);

    return 0;
}