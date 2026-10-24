#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

// Shared variables
mutex mtx;           // shared mutex M
int counter = 0;     // shared integer counter = 0[cite: 7]

const int N = 100000; // Repeat count for each thread

// Function executed by each thread
void safe_increment() {
    for (int i = 0; i < N; ++i) {
        // RAII lock acquisition inside thread body:[cite: 7]
        lock_guard<mutex> lock(mtx); // acquire_lock(M)[cite: 7]
        
        counter++;                   // Critical section[cite: 7]
        
        // release_lock(M) automatically happens when 'lock' goes out of scope[cite: 7]
    }
}

int main() {
    // 2 threads create karte hain jo safely counter ko increment karein ge
    thread t1(safe_increment);
    thread t2(safe_increment);

    // Dono threads ke finish hone ka wait karein
    t1.join();
    t2.join();

    // Expected value = Actual value (200000)
    cout << "Expected Counter Value: " << 2 * N << endl;
    cout << "Actual Counter Value:   " << counter << endl;

    return 0;
}