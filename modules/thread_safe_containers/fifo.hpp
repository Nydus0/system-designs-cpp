//
// Created by Nydus0 on 23/07/2025.
//

#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>

namespace safe {

    template<typename T> class fifo {
    public:

        template<typename U> void push(U&& value) {
            std::lock_guard lock(_mutex);
            _queue.push(std::forward<U>(value));
            _condition.notify_one();
        }

        T front() const {
            std::lock_guard lock(_mutex);
            if (!_queue.empty()) return _queue.front();
            return T();
        }

        T wait_and_pop() {
            std::unique_lock lock(_mutex);
            _condition.wait(lock, [this] { return !_queue.empty(); }); //wait until notified
            T value = std::move(_queue.front());
            _queue.pop();
            return value;
        }

        T timed_wait_and_pop(const std::chrono::milliseconds timeout) {
            std::unique_lock lock(_mutex);
            if (!_condition.wait_for(lock, timeout, [this] { return !_queue.empty(); })) {
                //timeout and still empty
                return T();
            }
            T value = std::move(_queue.front());
            _queue.pop();
            return value;
        }

        size_t size() const {
            return _queue.size();
        }

    private:
        std::condition_variable _condition;
        mutable std::mutex _mutex;
        std::queue<T> _queue;
    };

}
