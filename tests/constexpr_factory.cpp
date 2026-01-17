//
// Created by Nydus0 on 17/01/2026.
//

#include "modules/constexpr_factory/Factory.hpp"

#include <gtest/gtest.h>

TEST(factory, creation) {
    auto service1 = Service<TYPE1>();
    service1->foo1();

    auto service2 = Service<TYPE2>();
    service2->foo2();
}