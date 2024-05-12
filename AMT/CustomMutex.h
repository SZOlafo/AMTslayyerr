#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include<queue>
#ifndef CUSTOM_MUTEX_H
#define CUSTOM_MUTEX_H
class CustomMutex {
private:
    std::atomic<bool> locked = false;
    std::condition_variable cv;
    std::mutex cv_m;
public:

    void lock() {
        while (true) {
            bool expected = false;
            if (locked.compare_exchange_strong(expected, true, std::memory_order_acquire)) {
                break;
            }
            else {
                std::unique_lock<std::mutex> lk(cv_m);
                cv.wait(lk, [this] { return !locked.load(std::memory_order_relaxed); });
            }
        }
    }

    void unlock() {
        locked.store(false, std::memory_order_release);
        cv.notify_one();  
    }
};
#endif // CUSTOM_MUTEX_H
