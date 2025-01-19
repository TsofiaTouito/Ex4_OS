#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <mutex>

// Template class for Singleton Pattern
template <typename T>
class Singleton {
public:
    // Retrieve the Singleton instance
    inline static Singleton<T>& get_instance() {
        if (_instance == nullptr) {
            std::lock_guard<std::mutex> lock(_instance_mutex);
            if (_instance == nullptr) {
                _instance = new Singleton<T>();
            }
        }
        return *_instance;
    }

    // Destroy the Singleton instance
    inline static void destroy_instance() {
        std::lock_guard<std::mutex> lock(_instance_mutex);
        delete _instance;
        _instance = nullptr;
    }

    // Get the data stored in the Singleton instance
    inline const T& get_data() const { return _data; }

    // Set the data in the Singleton instance
    inline void set_data(const T& data) { _data = data; }

private:
    static Singleton<T>* _instance;      // Pointer to the Singleton instance
    static std::mutex _instance_mutex;  // Mutex for thread-safe access
    T _data;                            // Data stored in the Singleton instance

    // Private constructor to prevent direct instantiation
    inline Singleton() = default;

    // Disable copy constructor and assignment operator
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

// Initialize static members
template <typename T>
Singleton<T>* Singleton<T>::_instance = nullptr;

template <typename T>
std::mutex Singleton<T>::_instance_mutex;

#endif // SINGLETON_HPP
