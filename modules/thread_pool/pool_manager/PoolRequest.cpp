//
// Created by Nydus0 on 04/07/2025.
//

#include "modules/thread_pool/pool_manager/PoolRequest.hpp"

PoolRequest::POOL_TYPE PoolRequest::getPoolType() const {
    return _type;
}

const Arguments& PoolRequest::getArgs() const {
    return _args;
}
