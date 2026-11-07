// thread_safe_vector.hpp: starter code -- please refer to in-class example for ThreadSafeQueue
#ifndef THREAD_SAFE_VECTOR_HPP
#define THREAD_SAFE_VECTOR_HPP

#include <vector>
#include <mutex>
#include <condition_variable>

template <typename T>
class ThreadSafeVector{
private:
    std::vector<T> data;
    std::mutex mtx;
    std::condition_variable cv;

public:
    void push_back(const T& value){
        {
            std::lock_guard<std::mutex> lock(mtx);
            data.push_back(value);
        }
        cv.notify_one();
    }
    void wait_and_pop_back(T& value){
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() {return !data.empty();});
        value = data.back();
        data.pop_back();
    }
};

#endif
