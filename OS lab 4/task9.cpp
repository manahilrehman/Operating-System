#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex mtxA;
mutex mtxB;

// Thread 1: Acquire LockA -> sleep -> Acquire LockB
void thread1_routine() {
    cout << "Thread 1: Acquire LockA ki koshish kar raha hai..." << endl;
    lock_guard<mutex> lockA(mtxA); // std::lock_guard<std::mutex> lockA(mtxA);
    cout << "Thread 1: LockA mil gaya! Ab sleep kar raha hai..." << endl;

    this_thread::sleep_for(chrono::milliseconds(100)); // Sleep to guarantee race condition/circular wait

    cout << "Thread 1: LockB ki koshish kar raha hai..." << endl;
    lock_guard<mutex> lockB(mtxB); // std::lock_guard<std::mutex> lockB(mtxB);
    cout << "Thread 1: LockB bhi mil gaya!" << endl;
}

// Thread 2: Acquire LockB -> sleep -> Acquire LockA
void thread2_routine() {
    cout << "Thread 2: Acquire LockB ki koshish kar raha hai..." << endl;
    lock_guard<mutex> lockB(mtxB); // std::lock_guard<std::mutex> lockB(mtxB);[cite: 11]
    cout << "Thread 2: LockB mil gaya! Ab sleep kar raha hai..." << endl;

    this_thread::sleep_for(chrono::milliseconds(100)); // Sleep to guarantee race condition/circular wait

    cout << "Thread 2: LockA ki koshish kar raha hai..." << endl;
    lock_guard<mutex> lockA(mtxA); // std::lock_guard<std::mutex> lockA(mtxA);[cite: 11]
    cout << "Thread 2: LockA bhi mil gaya!" << endl;
}

int main() {
    cout << "Starting Deadlock Simulation..." << endl;

    thread t1(thread1_routine);
    thread t2(thread2_routine);

    t1.join();
    t2.join();

    cout << "Finished! (Deadlock na hone par yeh line print hogi)" << endl;

    return 0;
}