#include <iostream>
#include <thread>
#include <shared_mutex>
#include <chrono>

using namespace std;

// C++14 / C++11 compatible shared mutex
shared_timed_mutex rw_mtx;
int shared_data = 100;

// Reader function: Multiple readers can read concurrently
void reader(int id) {
    // Shared lock for reading
    shared_lock<shared_timed_mutex> r_lock(rw_mtx);
    
    cout << "Reader " << id << " read data: " << shared_data << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
}

// Writer function: Only one writer at a time
void writer(int id, int new_value) {
    // Exclusive lock for writing
    unique_lock<shared_timed_mutex> w_lock(rw_mtx);
    
    cout << "Writer " << id << " updating data to: " << new_value << endl;
    shared_data = new_value;
    this_thread::sleep_for(chrono::milliseconds(500));
}

int main() {
    thread r1(reader, 1);
    thread r2(reader, 2);
    thread w1(writer, 1, 200);
    thread r3(reader, 3);

    r1.join();
    r2.join();
    w1.join();
    r3.join();

    return 0;
}