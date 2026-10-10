#include <stdio.h>
#include <windows.h>

#define CAPACITY 3

// Queue structure for bounded buffer
int buffer[CAPACITY];
int count = 0;
int head = 0;
int tail = 0;

CRITICAL_SECTION mtx;
CONDITION_VARIABLE cv_producer;
CONDITION_VARIABLE cv_consumer;

// Producer Thread
DWORD WINAPI producer(LPVOID arg) {
    for (int item = 1; item <= 5; item++) {
        EnterCriticalSection(&mtx);

        // WHILE buffer.size() == CAPACITY: WAIT(cv_producer, mtx)
        while (count == CAPACITY) {
            SleepConditionVariableCS(&cv_producer, &mtx, INFINITE);
        }

        // buffer.PUSH(item)
        buffer[tail] = item;
        tail = (tail + 1) % CAPACITY;
        count++;

        printf("Produced: %d\n", item);

        // NOTIFY_ONE(cv_consumer)
        WakeConditionVariable(&cv_consumer);

        LeaveCriticalSection(&mtx);
        Sleep(100); // Small delay to observe interleaved execution
    }
    return 0;
}

// Consumer Thread
DWORD WINAPI consumer(LPVOID arg) {
    for (int i = 1; i <= 5; i++) {
        EnterCriticalSection(&mtx);

        // WHILE buffer.IS_EMPTY(): WAIT(cv_consumer, mtx)
        while (count == 0) {
            SleepConditionVariableCS(&cv_consumer, &mtx, INFINITE);
        }

        // item = buffer.POP()
        int item = buffer[head];
        head = (head + 1) % CAPACITY;
        count--;

        printf("Consumed: %d\n", item);

        // NOTIFY_ONE(cv_producer)
        WakeConditionVariable(&cv_producer);

        LeaveCriticalSection(&mtx);
        Sleep(150);
    }
    return 0;
}

int main() {
    HANDLE t_producer, t_consumer;

    InitializeCriticalSection(&mtx);
    InitializeConditionVariable(&cv_producer);
    InitializeConditionVariable(&cv_consumer);

    // Create threads
    t_producer = CreateThread(NULL, 0, producer, NULL, 0, NULL);
    t_consumer = CreateThread(NULL, 0, consumer, NULL, 0, NULL);

    // Wait for completion
    WaitForSingleObject(t_producer, INFINITE);
    WaitForSingleObject(t_consumer, INFINITE);

    // Clean up
    CloseHandle(t_producer);
    CloseHandle(t_consumer);
    DeleteCriticalSection(&mtx);

    return 0;
}