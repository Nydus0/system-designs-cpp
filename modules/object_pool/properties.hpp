//
// Created by Nydus0 on 21/06/2025.
//

#pragma once

#include <array>
#include <string>

class LargeObject {
public:
    void reset();
    std::string name();
    void setName(const std::string& name);

private:
    std::string _name;
    std::array<std::string, 10000> _arr;
};