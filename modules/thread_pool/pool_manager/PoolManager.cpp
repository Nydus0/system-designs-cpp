//
// Created by Nydus0 on 04/07/2025.
//

#include "PoolManager.hpp"

PoolManager::PoolManager() {
    _pools[PoolRequest::POOL_TYPE::IO] = std::make_unique<ThreadPool>(2);
    _pools[PoolRequest::POOL_TYPE::COMPUTE] = std::make_unique<ThreadPool>(4);
    _pools[PoolRequest::POOL_TYPE::LOGGING] = std::make_unique<ThreadPool>(1);
}
