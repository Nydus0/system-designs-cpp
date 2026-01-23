//
// Created by Nydus0 on 17/01/2026.
//

#include "modules/static_factory/services/Type1.hpp"
#include "modules/static_factory/services/Type2.hpp"
#include "modules/static_factory/services/Type3.hpp"

template <>
void Type1<ImplType::LIB2>::foo1() const
{
    std::cout << "foo type 1 lib 2" << std::endl;
}

template <>
void Type2<ImplType::LIB2>::foo2() const
{
    std::cout << "foo type 2 lib 2" << std::endl;
}

template <>
void Type3<ImplType::LIB2>::foo3() const
{
    std::cout << "foo type 3 lib 2" << std::endl;
}