cmake_minimum_required(VERSION 3.31)
project(system_designs_cpp)

set(CMAKE_CXX_STANDARD 26)

# enable and add subdirectory for tests
enable_testing()
add_subdirectory(tests)

# add modules library
add_subdirectory(modules)
target_include_directories(modules PUBLIC ${CMAKE_SOURCE_DIR})
