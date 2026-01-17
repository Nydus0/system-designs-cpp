//
// Created by Nydus0 on 17/01/2026.
//

#include "modules/constexpr_factory/Factory.hpp"

#include <gtest/gtest.h>

TEST(factory, creation) {
    auto service = Service<TYPE1>();
    service->foo();
}