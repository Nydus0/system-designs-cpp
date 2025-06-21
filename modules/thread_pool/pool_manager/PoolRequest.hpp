//
// Created by Nydus0 on 04/07/2025.
//

#pragma once

#include "modules/thread_pool/pool_manager/Arguments.hpp"

#include <utility>

class PoolRequest {
    /** @brief
     * PoolRequest class holds the pool type and the executable function arguments
     * **/

public:
    enum class POOL_TYPE {
        IO,
        COMPUTE,
        LOGGING
    };


    explicit PoolRequest(const POOL_TYPE t, Arguments a)
        : _type(t), _args(std::move(a)) {}

    [[nodiscard]] POOL_TYPE getPoolType() const;
    [[nodiscard]] const Arguments& getArgs() const;

private:
    POOL_TYPE _type;
    Arguments _args;
};


