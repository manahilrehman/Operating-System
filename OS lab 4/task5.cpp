#include <iostream>
#include <thread>
#include <vector>

using namespace std;

// Shared counter variable
int counter = 0; // shared integer counter = 0

const int N = 100000; // Repeat count for each thread

// Function executed by each thread
void increment_routine() {
    for (int i = 0; i < N; ++i) {
        // Non-atomic read-modify-write causes lost updates
        int temp = counter; // Load
        temp = temp + 1;    // Modify[cite: 6]
        counter = temp;     // Store (Interleaving here causes loss)[cite: 6]
    }
}

int main() {
    // 2 threads create karte hain jo same counter ko update karein ge
    thread t1(increment_routine);
    thread t2(increment_routine);

    // Dono threads ke finish hone ka wait karein
    t1.join();
    t2.join();

    // Expected answer: 200000 (2 * 100000)
    // Actual answer: Less than 200000 due to data race / lost updates[cite: 6]
    cout << "Expected Counter Value: " << 2 * N << endl;
    cout << "Actual Counter Value:   " << counter << endl;

    return 0;
}