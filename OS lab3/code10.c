#include <stdio.h>
#include <windows.h>

int shared_data = 0;       // GLOBAL shared_data = 0
SRWLOCK rw_lock;           // GLOBAL rw_lock = CREATE_SHARED_MUTEX()

typedef struct {
    int id;
    int val;
} ThreadData;

// Reader Thread Function
DWORD WINAPI reader(LPVOID arg) {
    ThreadData *data = (ThreadData *)arg;

    // LOCK_SHARED(rw_lock)
    AcquireSRWLockShared(&rw_lock);

    printf("Reader %d read value: %d\n", data->id, shared_data);

    // UNLOCK_SHARED(rw_lock)
    ReleaseSRWLockShared(&rw_lock);

    return 0;
}

// Writer Thread Function
DWORD WINAPI writer(LPVOID arg) {
    ThreadData *data = (ThreadData *)arg;

    // LOCK_EXCLUSIVE(rw_lock)
    AcquireSRWLockExclusive(&rw_lock);

    shared_data = data->val;
    printf("Writer %d updated value to: %d\n", data->id, shared_data);

    // UNLOCK_EXCLUSIVE(rw_lock)
    ReleaseSRWLockExclusive(&rw_lock);

    return 0;
}

int main() {
    // Initialize SRW Lock
    InitializeSRWLock(&rw_lock);

    HANDLE h_writer1, h_reader1, h_reader2, h_writer2, h_reader3;
    ThreadData w1 = {1, 42};
    ThreadData r1 = {1, 0};
    ThreadData r2 = {2, 0};
    ThreadData w2 = {2, 99};
    ThreadData r3 = {3, 0};

    // First sequence: Writer 1 updates to 42, then Readers 1 & 2 read
    h_writer1 = CreateThread(NULL, 0, writer, &w1, 0, NULL);
    WaitForSingleObject(h_writer1, INFINITE);

    h_reader1 = CreateThread(NULL, 0, reader, &r1, 0, NULL);
    h_reader2 = CreateThread(NULL, 0, reader, &r2, 0, NULL);
    WaitForSingleObject(h_reader1, INFINITE);
    WaitForSingleObject(h_reader2, INFINITE);

    // Second sequence: Writer 2 updates to 99, then Reader 3 reads
    h_writer2 = CreateThread(NULL, 0, writer, &w2, 0, NULL);
    WaitForSingleObject(h_writer2, INFINITE);

    h_reader3 = CreateThread(NULL, 0, reader, &r3, 0, NULL);
    WaitForSingleObject(h_reader3, INFINITE);

    // Clean up handles
    CloseHandle(h_writer1);
    CloseHandle(h_reader1);
    CloseHandle(h_reader2);
    CloseHandle(h_writer2);
    CloseHandle(h_reader3);

    return 0;
}