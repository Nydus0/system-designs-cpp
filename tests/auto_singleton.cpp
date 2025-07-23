//
// Created by Nydus0 on 19/07/2025.
//

#include "modules/auto_singleton/AutoSingleton.hpp"

#include <gtest/gtest.h>

class MyService {
public:
    MyService()  { std::cout << "MyService created\n"; }
    ~MyService() { std::cout << "MyService destroyed\n"; }

    void run() { std::cout << "Running service...\n"; }
};

TEST(auto_singleton, create) {

    EXPECT_NO_THROW({
        auto& service = AutoSingleton<MyService>::get();
        service.run();
    });
}

TEST(auto_singleton, destroy) {
    auto& service = AutoSingleton<MyService>::get();

    EXPECT_NO_THROW({
        //optional: manually destroy early
        AutoSingleton<MyService>::destroy();
    });
}
