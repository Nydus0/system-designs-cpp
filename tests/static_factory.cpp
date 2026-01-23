//
// Created by Nydus0 on 17/01/2026.
//

#include "modules/static_factory/services/Type1.hpp"
#include "modules/static_factory/services/Type2.hpp"
#include "modules/static_factory/services/Type3.hpp"
#include "tests/utility/output.hpp"

TEST(static_factory, check_implementation)
{
    //create services and check their implementation (LIB2)
    auto service1 = Service<TYPE1>();
    auto output1 = captureCout([&service1]() { service1->foo1();} );
    EXPECT_EQ(output1, "foo type 1 lib 2\n");

    auto service2 = Service<TYPE2>();
    auto output2 = captureCout([&service2]() { service2->foo2();} );
    EXPECT_EQ(output2, "foo type 2 lib 2\n");

    auto service3 = Service<TYPE3>();
    auto output3 = captureCout([&service3]() { service3->foo3();} );
    EXPECT_EQ(output3, "foo type 3 lib 2\n");
}