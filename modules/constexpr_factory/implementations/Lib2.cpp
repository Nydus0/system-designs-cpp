//
// Created by Nydus0 on 17/01/2026.
//

#include "modules/constexpr_factory/Type1.hpp"
#include "modules/constexpr_factory/Definitions.hpp"

template <>
void Type1<ImplType::LIB2>::foo() const
{
    std::cout << "foo type1 lib 2" << std::endl;
}
