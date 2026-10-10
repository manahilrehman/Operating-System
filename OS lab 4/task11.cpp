#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtxA;
mutex mtxB;

// Deadlock-free multi-locking using C++11 lock() + lock_guard
void transfer_funds(int accountA, int accountB) {
    // Atomically lock both mutexes without deadlock
    lock(mtxA, mtxB);
    
    // Adopt the already-locked mutexes into lock_guards for RAII cleanup
    lock_guard<mutex> lockA(mtxA, adopt_lock);
    lock_guard<mutex> lockB(mtxB, adopt_lock);
    
    cout << "Atomically locked both mtxA and mtxB for transfer from Account " 
         << accountA << " to Account " << accountB << endl;
}

int main() {
    thread t1(transfer_funds, 1, 2);
    thread t2(transfer_funds, 2, 1);

    t1.join();
    t2.join();

    cout << "Execution completed safely without deadlock!" << endl;

    return 0;
}