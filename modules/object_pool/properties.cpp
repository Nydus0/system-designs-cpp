//
// Created by Nydus0 on 21/06/2025.
//

#include "modules/object_pool/properties.hpp"

using namespace std;

void LargeObject::reset() {
    _arr.fill("");
}

string LargeObject::name() { return _name; }

void LargeObject::setName(const std::string& name) {
    _name = name;
}
