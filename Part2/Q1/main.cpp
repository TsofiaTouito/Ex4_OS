#include "singleton.hpp"
#include <iostream>
#include <thread>

// Function to demonstrate Singleton usage in Thread 1
void thread1_function(int new_data) {
    // Retrieve the Singleton instance
    Singleton<int>& singleton_instance = Singleton<int>::get_instance();

    // Display the initial data stored in the Singleton
    std::string message = "Thread 1 initial data: " + std::to_string(singleton_instance.get_data());
    std::cout << message << std::endl;

    // Simulate work by sleeping for 10 milliseconds
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    // Set new data in the Singleton instance
    message = "Thread 1 updating data to: " + std::to_string(new_data);
    std::cout << message << std::endl;
    singleton_instance.set_data(new_data);

    // Display the updated data
    message = "Thread 1 updated data: " + std::to_string(singleton_instance.get_data());
    std::cout << message << std::endl;
}

// Function to demonstrate Singleton usage in Thread 2
void thread2_function() {
    // Retrieve the Singleton instance
    Singleton<int>& singleton_instance = Singleton<int>::get_instance();

    // Display the initial data stored in the Singleton
    std::string message = "Thread 2 initial data: " + std::to_string(singleton_instance.get_data());
    std::cout << message << std::endl;

    // Simulate work by sleeping for 20 milliseconds
    std::this_thread::sleep_for(std::chrono::milliseconds(20));

    // Display the data after sleeping
    message = "Thread 2 data after sleep: " + std::to_string(singleton_instance.get_data());
    std::cout << message << std::endl;
}

int main() {
    // Retrieve Singleton instance references
    Singleton<int>& singleton_instance1 = Singleton<int>::get_instance();
    Singleton<int>& singleton_instance2 = Singleton<int>::get_instance();

    // Demonstrate that both references point to the same instance
    std::cout << "Setting data in singleton_instance1 to 5" << std::endl;
    singleton_instance1.set_data(5);
    std::cout << "singleton_instance1: " << singleton_instance1.get_data()
              << " singleton_instance2: " << singleton_instance2.get_data() << std::endl;

    std::cout << "Setting data in singleton_instance2 to 10" << std::endl;
    singleton_instance2.set_data(10);
    std::cout << "singleton_instance1: " << singleton_instance1.get_data()
              << " singleton_instance2: " << singleton_instance2.get_data() << std::endl;

    // Create and start threads
    std::thread thread1(thread1_function, 15);
    std::thread thread2(thread2_function);

    // Wait for threads to complete
    thread1.join();
    thread2.join();

    return 0;
}
