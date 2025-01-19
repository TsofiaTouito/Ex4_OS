#include <iostream>
#include <thread>
#include <mutex>
#include "guard.hpp"

// Mutex to synchronize access to the shared counter
std::mutex shared_counter_mutex;

// Shared counter variable to be incremented
int shared_counter = 0;

// Function to safely increment the shared counter
void increment_shared_counter() {
    // Lock the mutex using Guard to ensure safe access
    Guard lock_guard(shared_counter_mutex);
    shared_counter++;
}

int main() {
    std::cout << "Incrementing shared counter 100,000 times using multiple threads:" << std::endl;

    // Launch threads to increment the shared counter
    for (int i = 0; i < 100000; i++) {
        std::thread worker_thread(increment_shared_counter);
        worker_thread.detach(); // Detach the thread to run independently
    }

    // Allow threads to complete execution
    std::cout << "Waiting for threads to finish..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    // Display the final value of the shared counter
    std::cout << "Final value of the shared counter: " << shared_counter << std::endl;

    return 0;
}
