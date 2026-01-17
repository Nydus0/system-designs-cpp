//
// Created by Nydus0 on 17/01/2026.
//

#pragma once

#include "modules/constexpr_factory/Definitions.hpp"
#include "modules/constexpr_factory/Type1.hpp"
#include "modules/constexpr_factory/Type2.hpp"
#include "modules/constexpr_factory/Type3.hpp"

template <ServiceType> class Service {}; //forward declaration

template <> class Service<TYPE1>
{
    using currType1 = Type1<CURR_IMPL>;
    currType1 _instance {};
public:
    currType1 *operator->() { return &_instance; }
};

template <> class Service<TYPE2>
{
    using currType2 = Type2<CURR_IMPL>;
    currType2 _instance {};
public:
    currType2 *operator->() { return &_instance; }
};

template <> class Service<TYPE3>
{
    using currType3 = Type3<CURR_IMPL>;
    currType3 _instance {};
public:
    currType3 *operator->() { return &_instance; }
};




