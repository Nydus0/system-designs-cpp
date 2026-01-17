//
// Created by Nydus0 on 17/01/2026.
//
#pragma once

#include <iostream>

enum class ServiceType {TYPE1, TYPE2, TYPE3};
enum class ImplType {LIB1, LIB2};

constexpr ServiceType TYPE1 = ServiceType::TYPE1;
constexpr ServiceType TYPE2 = ServiceType::TYPE2;
constexpr ServiceType TYPE3 = ServiceType::TYPE3;

static constexpr ImplType CURR_IMPL = ImplType::LIB1;