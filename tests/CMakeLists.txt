# install gtest dependency
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/7e17b15f1547bb8dd9c2fed91043b7af3437387f.zip
)

# for windows: prevent overriding the parent project's compiler/linker settings
FetchContent_MakeAvailable(googletest)

# create test executable
add_executable(tests
        auto_singleton.cpp
        bimap.cpp
        object_pool.cpp
        static_factory.cpp
        thread_pool.cpp
        thread_safe_containers.cpp
        instance_provider.cpp)

# link with library and GTest
target_link_libraries(tests
        PRIVATE
        modules
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)





