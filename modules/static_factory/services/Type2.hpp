//
// Created by Nydus0 on 17/01/2026.
//

#pragma once

#include "modules/static_factory/Factory.hpp"


template <ImplType> class Type2 {

public:
    void foo2() const;
};

constexpr ServiceType TYPE2 = ServiceType::TYPE2;
template <> class Service<TYPE2> : public ServiceModel<Type2<CURR_IMPL>> {};