#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

using namespace std;

queue<int> q;
mutex mtx;
condition_variable cv;

// Producer side logic
void producer() {
    for (int i = 1; i <= 5; ++i) {
        {
            unique_lock<mutex> lock(mtx);
            q.push(i);
            cout << "Producer: pushed item " << i << " into queue" << endl;
            
            // Producer side signal
            cv.notify_one(); // cv.notify_one();
        }
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

// Consumer side logic
void consumer() {
    for (int i = 1; i <= 5; ++i) {
        // Consumer side lock
        unique_lock<mutex> lock(mtx); // std::unique_lock<std::mutex> lock(mtx);
        
        // Wait until queue is not empty (Releases mutex and puts thread to sleep)
        cv.wait(lock, [] { return !q.empty(); }); // cv.wait(lock, [] { return !queue.empty(); });
        
        int item = q.front();
        q.pop();
        cout << "Consumer: popped item " << item << " from queue" << endl;
        
        lock.unlock();
    }
}

int main() {
    thread t1(producer);
    thread t2(consumer);

    t1.join();
    t2.join();

    cout << "Process finished successfully!" << endl;

    return 0;
}