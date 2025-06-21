//
// Created by Nydus0 on 04/07/2025.
//

#pragma once

#include "modules/thread_pool/ThreadPool.hpp"
#include "modules/thread_pool/pool_manager/PoolRequest.hpp"

#include <map>

class PoolManager {
    /** @brief
     * This class receives functions of any type and the pool requests containing function arguments and dispatches
     * the request to the correct thread pool.
     * **/
public:
    PoolManager();

    template<typename F>
    auto submit(const PoolRequest &request, F&& f);

private:
    std::map<PoolRequest::POOL_TYPE, std::unique_ptr<ThreadPool> > _pools;
};

template<typename F>
auto PoolManager::submit(const PoolRequest &request, F&& f) {

    const auto it = _pools.find(request.getPoolType());

    if (it == _pools.end()) { throw std::runtime_error("Invalid pool type"); }

    return it->second->enqueue(std::forward<F>(f), request.getArgs());
}
