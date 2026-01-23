//
// Created by Nydus0 on 17/01/2026.
//

#pragma once

#include "modules/static_factory/Factory.hpp"

template <ImplType> class Type3 {

public:
    void foo3() const;
};

constexpr ServiceType TYPE3 = ServiceType::TYPE3;
template <> class Service<TYPE3> : public ServiceModel<Type3<CURR_IMPL>> {};