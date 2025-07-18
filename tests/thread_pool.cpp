//
// Created by Nydus0 on 19/07/2025.
//

#include <gtest/gtest.h>

#include "modules/thread_pool/ThreadPool.hpp"
#include "modules/thread_pool/pool_manager/PoolManager.hpp"
#include "modules/thread_pool/pool_manager/PoolRequest.hpp"

int print_sum(const int a, const int b) { return a + b; }
int add(const int a, const int b) { return a + b; }
std::string greet(const std::string& name) { return "Hello, " + name; }

TEST(thread_pool, Arguments) {
    Arguments args;
    args.add(3);
    args.add(5);

    Arguments args2;
    args2.add(std::string("Coco"));

    EXPECT_EQ(std::any_cast<int>(args.getAll()[0]), 3);
    EXPECT_EQ(std::any_cast<int>(args.getAll()[1]), 5);
    EXPECT_EQ(args.getAll().size(), 2);

    EXPECT_EQ(std::any_cast<std::string>(args2.getAll()[0]), "Coco");
    EXPECT_EQ(args2.getAll().size(), 1);
}

TEST(thread_pool, PoolRequest) {
    // create the argument holders
    Arguments args; args.add(3); args.add(5);
    Arguments args2; args2.add(3); args2.add(4);
    Arguments args3; args3.add(std::string("Coco"));

    // package them in a request
    const PoolRequest request(PoolRequest::POOL_TYPE::COMPUTE, args);
    const PoolRequest request2(PoolRequest::POOL_TYPE::LOGGING, args2);
    const PoolRequest request3(PoolRequest::POOL_TYPE::COMPUTE, args3);


    EXPECT_EQ(request.getPoolType(), PoolRequest::POOL_TYPE::COMPUTE);
    EXPECT_EQ(request2.getPoolType(), PoolRequest::POOL_TYPE::LOGGING);
    EXPECT_EQ(request3.getPoolType(), PoolRequest::POOL_TYPE::COMPUTE);

    EXPECT_EQ(std::any_cast<int>(request.getArgs()[0]), 3);
    EXPECT_EQ(std::any_cast<int>(request.getArgs()[1]), 5);
    EXPECT_EQ(std::any_cast<int>(request2.getArgs()[0]), 3);
    EXPECT_EQ(std::any_cast<int>(request2.getArgs()[1]), 4);
    EXPECT_EQ(std::any_cast<std::string>(request3.getArgs()[0]), "Coco");
}

TEST(thread_pool, PoolManager) {
    // create the argument holders
    Arguments args; args.add(3); args.add(5);
    Arguments args2; args2.add(3); args2.add(4);
    Arguments args3; args3.add(std::string("Coco"));

    // package them in a request
    const PoolRequest request(PoolRequest::POOL_TYPE::COMPUTE, args);
    const PoolRequest request2(PoolRequest::POOL_TYPE::LOGGING, args2);
    const PoolRequest request3(PoolRequest::POOL_TYPE::COMPUTE, args3);

    // submit the function and get the result
    PoolManager manager;
    auto future = manager.submit(request, add);
    auto future2 = manager.submit(request2, print_sum);
    auto future3 = manager.submit(request3, greet);

    EXPECT_EQ(future.get(), 8);
    EXPECT_EQ(future2.get(), 7);
    EXPECT_EQ(future3.get(), "Hello, Coco");
}