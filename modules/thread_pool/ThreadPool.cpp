//
// Created by Nydus0 on 21/06/2025.
//

#include "modules/thread_pool/ThreadPool.hpp"


ThreadPool::ThreadPool(const size_t nbWorkers) {
    for (size_t i = 0; i < nbWorkers; i++) {
        _workers.emplace_back([this] { this->workerLoop(); });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock lock(_queue_mutex);
        _stop = true;
    }
    _queue_condition.notify_all();
    for (auto &worker: _workers) { worker.join(); }
}

void ThreadPool::workerLoop() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock lock(_queue_mutex);
            _queue_condition.wait(lock, [this]() { return _stop || !_tasks.empty(); });
            if (_stop && _tasks.empty()) { return; }

            task = std::move(_tasks.front());
            _tasks.pop();
        }

        //run task
        task();
    }
}