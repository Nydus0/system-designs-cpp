//
// Created by Nydus0 on 17/01/2026.
//

#pragma once

#include "modules/static_factory/services/Type1.hpp"
#include "modules/static_factory/services/Type2.hpp"
#include "modules/static_factory/services/Type3.hpp"

template <ServiceType> class Service {};

// generic base template
template <typename T> class ServiceModel {
protected:
    T _instance{};
public:
    T* operator->() {
        return &_instance;
    }
};

// add new types here
template <> class Service<TYPE1> : public ServiceModel<Type1<CURR_IMPL>> {};
template <> class Service<TYPE2> : public ServiceModel<Type2<CURR_IMPL>> {};
template <> class Service<TYPE3> : public ServiceModel<Type3<CURR_IMPL>> {};



