#include <iostream>
#include <thread>

using namespace std;

// Function executed by the child thread (child_routine)
void child_routine() {
    cout << "Child executing with unique thread ID: " 
         << this_thread::get_id() << endl;
}

int main() {
    // Spawn child thread running child_routine
    thread t(child_routine);

    // Wait for the thread to finish before main exits
    t.join(); // Blocks calling thread until 't' finishes

    cout << "Main thread exiting..." << endl;

    return 0;
}