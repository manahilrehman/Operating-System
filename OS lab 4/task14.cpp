#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

using namespace std;

// C++11 Custom Counting Semaphore
class CountingSemaphore {
private:
    mutex mtx;
    condition_variable cv;
    int count;

public:
    CountingSemaphore(int permits) : count(permits) {}

    // Decrements permit count (Blocks if count == 0)
    void acquire() {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this]() { return count > 0; });
        --count;
    }

    // Returns permit / increment_or_signal
    void release() {
        unique_lock<mutex> lock(mtx);
        ++count;
        cv.notify_one();
    }
};

// 3 permits max
CountingSemaphore sem(3);

void task(int thread_id) {
    cout << "Thread " << thread_id << " is waiting for a permit..." << endl;
    
    sem.acquire(); // Decrements permit count
    
    cout << "[Access Granted] Thread " << thread_id << " is executing task..." << endl;
    this_thread::sleep_for(chrono::seconds(1)); // Perform task
    
    cout << "Thread " << thread_id << " finished. Releasing permit." << endl;
    
    sem.release(); // Returns permit
}

int main() {
    vector<thread> threads;

    for (int i = 1; i <= 6; ++i) {
        threads.push_back(thread(task, i));
    }

    for (auto& t : threads) {
        t.join();
    }

    cout << "All tasks completed successfully!" << endl;

    return 0;
}