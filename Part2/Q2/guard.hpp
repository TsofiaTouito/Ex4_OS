#ifndef GUARD_HPP
#define GUARD_HPP

#include <mutex>

/**
 * @class Guard
 * @brief A RAII-style mutex lock guard to ensure safe and automatic locking and unlocking of a mutex.
 *
 * The Guard class acquires a lock on a given mutex during its construction
 * and automatically releases the lock when it goes out of scope.
 * This approach minimizes the risk of deadlocks and ensures exception safety.
 */
class Guard {
public:
    /**
     * @brief Constructs a Guard and locks the provided mutex.
     * @param mtx The mutex to lock.
     */
    inline Guard(std::mutex& mtx) : _mutex(mtx) { _mutex.lock(); }

    /**
     * @brief Destructs the Guard and unlocks the mutex.
     */
    inline ~Guard() { _mutex.unlock(); }

    // Deleted copy constructor and copy assignment operator
    Guard(const Guard&) = delete;
    Guard& operator=(const Guard&) = delete;

private:
    std::mutex& _mutex; ///< Reference to the mutex being locked
};

#endif // GUARD_HPP
