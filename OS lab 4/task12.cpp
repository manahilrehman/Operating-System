#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

using namespace std;

queue<int> buffer;
const unsigned int MAX_BUFFER_SIZE = 5;

mutex mtx;
condition_variable cv_producer, cv_consumer;

// Producer function
void producer(int items_to_produce) {
    for (int i = 1; i <= items_to_produce; ++i) {
        unique_lock<mutex> lock(mtx);

        // Wait if buffer is full (prevents CPU busy-waiting)
        cv_producer.wait(lock, [] { return buffer.size() < MAX_BUFFER_SIZE; });

        buffer.push(i);
        cout << "[Producer] Produced item: " << i << " | Buffer size: " << buffer.size() << endl;

        // Notify consumer thread that an item is available
        cv_consumer.notify_one();
        
        lock.unlock();
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

// Consumer function
void consumer(int items_to_consume) {
    for (int i = 1; i <= items_to_consume; ++i) {
        unique_lock<mutex> lock(mtx);

        // Wait if buffer is empty (eliminates CPU busy-waiting)
        cv_consumer.wait(lock, [] { return !buffer.empty(); });

        int val = buffer.front();
        buffer.pop();
        cout << "  [Consumer] Consumed item: " << val << " | Buffer size: " << buffer.size() << endl;

        // Notify producer thread that space is available
        cv_producer.notify_one();

        lock.unlock();
        this_thread::sleep_for(chrono::milliseconds(300));
    }
}

int main() {
    int total_items = 10;

    thread prod(producer, total_items);
    thread cons(consumer, total_items);

    prod.join();
    cons.join();

    cout << "Producer-Consumer queue completed successfully!" << endl;

    return 0;
}