//
// Created by Nydus0 on 17/01/2026.
//

#include "modules/constexpr_factory/Type1.hpp"
#include "modules/constexpr_factory/Type2.hpp"
#include "modules/constexpr_factory/Definitions.hpp"

template <>
void Type1<ImplType::LIB1>::foo1() const
{
   std::cout << "foo type 1 lib 1" << std::endl;
}

template <>
void Type2<ImplType::LIB1>::foo2() const
{
   std::cout << "foo type 2 lib 1" << std::endl;
}