//
// Created by Nydus0 on 17/01/2026.
//

#pragma once

#include "modules/static_factory/Factory.hpp"

template <ImplType> class Type1 {

public:
    void foo1() const;
};

constexpr ServiceType TYPE1 = ServiceType::TYPE1;
template <> class Service<TYPE1> : public ServiceModel<Type1<CURR_IMPL>> {};