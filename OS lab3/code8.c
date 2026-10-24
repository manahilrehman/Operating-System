#include <stdio.h>
#include <windows.h>

int counter = 0;      // GLOBAL counter = 0
HANDLE mtx;           // GLOBAL mtx = CREATE_MUTEX()

// Safe increment function protected by mutex
DWORD WINAPI safe_increment(LPVOID arg) {
    for (int i = 0; i < 100000; i++) {
        // LOCK(mtx)
        WaitForSingleObject(mtx, INFINITE);

        counter = counter + 1; // Critical Section

        // UNLOCK(mtx)
        ReleaseMutex(mtx);
    }
    return 0;
}

int main() {
    HANDLE thread1, thread2;

    // CREATE_MUTEX()
    mtx = CreateMutex(NULL, FALSE, NULL);

    // SPAWN thread1 and thread2
    thread1 = CreateThread(NULL, 0, safe_increment, NULL, 0, NULL);
    thread2 = CreateThread(NULL, 0, safe_increment, NULL, 0, NULL);

    // JOIN thread1 and thread2
    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);

    // Print output protected by mutex
    printf("Final counter with Mutex: %d\n", counter);

    // Clean up handles
    CloseHandle(thread1);
    CloseHandle(thread2);
    CloseHandle(mtx);

    return 0;
}