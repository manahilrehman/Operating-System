#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

// Shared lock-free atomic counter
atomic<int> counter{0}; // std::atomic<int> counter{0};

const int N = 100000; // Repeat count for each thread

// Function executed by each thread
void atomic_worker() {
    for (int i = 0; i < N; ++i) {
        // Direct hardware atomic fetch and add without OS lock/context switch
        counter.fetch_add(1, memory_order_relaxed); //[cite: 8]
    }
}

int main() {
    // 2 threads create karte hain jo atomic counter ko increment karein ge
    thread t1(atomic_worker);
    thread t2(atomic_worker);

    // Dono threads ke finish hone ka wait karein
    t1.join();
    t2.join();

    // Expected value = Actual value (200000)
    cout << "Expected Counter Value: " << 2 * N << endl;
    cout << "Actual Counter Value:   " << counter << endl;

    return 0;
}