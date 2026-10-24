#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

// Worker function
void worker_fn() {
    cout << "Worker thread start ho gaya hai..." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Worker thread ne kaam khatam kar liya." << endl;
}

int main() {
    cout << "Main function start hua." << endl;

    { // Scope start
        thread t(worker_fn);
        
        cout << "Thread object create ho chuka hai..." << endl;

        // Manual join to achieve same behavior
        t.join();
    } // Scope exit

    cout << "Main function end ho gaya." << endl;

    return 0;
}
