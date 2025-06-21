//
// Created by Nydus0 on 05/07/2025.
//

#include "Arguments.hpp"

const std::any& Arguments::operator[](const size_t index) const {
    return args.at(index);
}

size_t Arguments::size() const {
    return args.size();
}

[[nodiscard]] const std::vector<std::any>& Arguments::getAll() const {
    return args;
}