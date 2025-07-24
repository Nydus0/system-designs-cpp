add_library(modules STATIC
        #thread_pool
        thread_pool/pool_manager/PoolManager.cpp
        thread_pool/pool_manager/PoolRequest.cpp
        thread_pool/pool_manager/Arguments.cpp
        thread_pool/ThreadPool.cpp

        #safe_containers
        thread_safe_containers/fifo.hpp
        thread_safe_containers/vector.hpp
        bimap/BiMap.hpp)