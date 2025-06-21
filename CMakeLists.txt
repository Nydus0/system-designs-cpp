cmake_minimum_required(VERSION 3.31)
project(design_patterns_cpp)

set(CMAKE_CXX_STANDARD 26)

add_executable(test
        test/main.cpp
        object_pool/properties.cpp
)

target_include_directories(test
        PRIVATE
        ${CMAKE_SOURCE_DIR}
)

