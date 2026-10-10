#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

// Logger function jo background (daemon) thread mein chalegi
void logger() {
    while (true) {
        cout << "[Daemon] Flushing buffer to disk..." << endl;
        // 5 seconds sleep (demonstration ke liye 1 second rakha hai taaki output jaldi dikhe)
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main() {
    // Logger thread spawn karein
    thread t(logger);

    // Thread ko detach karein taaki yeh background mein azadana chale
    t.detach(); // OS manages PCB/TCB deallocation upon thread termination

    cout << "Main thread chal raha hai..." << endl;

    // Main thread ko thoda time dein taaki detached thread ki execution nazar aaye
    this_thread::sleep_for(chrono::seconds(3));

    cout << "Main thread khatam ho raha hai..." << endl;

    return 0; // Main thread khatam hotay hi process terminate ho jayega
}