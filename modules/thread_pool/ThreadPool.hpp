//
// Created by Nydus0 on 21/06/2025.
//

#pragma once

#include "modules/thread_pool/pool_manager/Arguments.hpp"
#include "modules/thread_pool/pool_manager/function_traits.hpp"

#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>

class ThreadPool {

    /** @brief ThreadPool class
     *
     * This class implements a thread pool with a fixed number of worker threads
     * that continuously pull tasks from a queue and execute them.
     *
     * The key feature here is the ability to enqueue any callable with a dynamic
     * set of arguments wrapped in an `Arguments` object, without knowing
     * the argument types at enqueue time.
     *
     * To achieve this, the class contains a chain of template methods:
     *
     * enqueue(...)      -> public API that accepts a callable and an Arguments object,
     *                     wraps the invocation in a packaged_task, and schedules it.
     *
     * invoke(...)       -> deduces the function argument types via function_traits,
     *                     then forwards to invoke_tuple_impl().
     *
     * invoke_tuple_impl -> unpacks the tuple of argument types and calls invoke_impl().
     *
     * invoke_impl(...)  -> finally calls std::invoke() on the callable,
     *                     casting each std::any argument to the expected type.
     *
     * This chain allows type-erased arguments to be correctly cast and passed to any
     * callable, enabling flexible and safe task scheduling.
     */


public:
    explicit ThreadPool(size_t nbWorkers);
    ~ThreadPool();

    template<typename F>
    auto enqueue(F &&f, Arguments args)
    -> std::future<typename function_traits<std::decay_t<F>>::return_type>;

private:
    void workerLoop();
    template <typename F> auto invoke(F&& f, const Arguments& args);
    template <typename F, typename... Args, std::size_t... I> auto invoke_impl(F&& f, const std::vector<std::any>& anyArgs, std::index_sequence<I...>);
    template<typename F, typename Tuple, std::size_t... I> auto invoke_tuple_impl(F&& f, const Arguments& args, std::index_sequence<I...>);

    size_t NB_THREADS{};
    std::atomic_bool _stop {false};
    std::vector<std::thread> _workers;
    std::queue<std::function<void()>> _tasks;
    std::condition_variable _queue_condition;
    std::mutex _queue_mutex;
};

template <typename F, typename... Args, std::size_t... I>
auto ThreadPool::invoke_impl(F&& f, const std::vector<std::any>& anyArgs, std::index_sequence<I...>) {
    return std::invoke(std::forward<F>(f), std::any_cast<Args>(anyArgs[I])...);
}

template<typename F, typename Tuple, std::size_t... I>
auto ThreadPool::invoke_tuple_impl(F&& f, const Arguments& args, std::index_sequence<I...>) {
    return invoke_impl<F, std::tuple_element_t<I, Tuple>...>(
        std::forward<F>(f),
        args.getAll(),
        std::index_sequence<I...> {}
    );
}

template <typename F>
auto ThreadPool::invoke(F&& f, const Arguments& args) {
    using traits = function_traits<std::decay_t<F>>;
    using Tuple = typename traits::args_tuple;

    constexpr auto N = std::tuple_size_v<Tuple>;
    return invoke_tuple_impl<F, Tuple>(
        std::forward<F>(f),
        args,
        std::make_index_sequence<N>{}
    );
}

template<typename F>
auto ThreadPool::enqueue(F&& f, Arguments args)
-> std::future<typename function_traits<std::decay_t<F>>::return_type> {

    using traits = function_traits<std::decay_t<F>>;
    using return_type = typename traits::return_type;

    auto task = std::make_shared<std::packaged_task<return_type()>>(
        [this, func = std::forward<F>(f), args = std::move(args)]() mutable {
            return invoke(func, args); //invokes deduces the args
        }
    );
    std::future<return_type> res = task->get_future();

    {
        std::unique_lock lock(_queue_mutex);
        if (_stop) { throw std::runtime_error("enqueue on stopped ThreadPool"); }

        _tasks.emplace([task]() { (*task)(); });
    }

    _queue_condition.notify_one();
    return res;
}
