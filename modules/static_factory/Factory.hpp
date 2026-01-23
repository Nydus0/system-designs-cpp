//
// Created by Nydus0 on 17/01/2026.
//

#pragma once

#include "modules/static_factory/Definitions.hpp"

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



