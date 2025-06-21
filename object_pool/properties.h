//
// Created by Nydus0 on 21/06/2025.
//

#ifndef object_pool_properties_H
#define object_pool_properties_H

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

#endif
