cmake_minimum_required(VERSION 3.31)
project(design_patterns_cpp)

set(CMAKE_CXX_STANDARD 26)

add_executable(tests

        ## tests ##
        tests/main.cpp

        ## modules ##

        #object pool
        modules/object_pool/properties.cpp

        #thread pool
        modules/thread_pool/ThreadPool.cpp
        modules/thread_pool/properties.cpp
        modules/thread_pool/pool_manager/PoolManager.cpp
        modules/thread_pool/pool_manager/PoolRequest.cpp
        modules/thread_pool/pool_manager/Arguments.cpp
)

target_include_directories(tests
        PRIVATE
        ${CMAKE_SOURCE_DIR}
)

