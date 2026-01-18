add_library(modules STATIC
        #thread_pool
        thread_pool/pool_manager/PoolManager.cpp
        thread_pool/pool_manager/PoolRequest.cpp
        thread_pool/pool_manager/Arguments.cpp
        thread_pool/ThreadPool.cpp

        #safe_containers
        thread_safe_containers/fifo.hpp
        thread_safe_containers/vector.hpp
        bimap/BiMap.hpp

        #constexpr factory
        constexpr_factory/Factory.hpp
        constexpr_factory/implementations/Lib1.cpp
        constexpr_factory/implementations/Lib2.cpp)