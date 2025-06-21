//
// Created by Nydus0 on 05/07/2025.
//

#pragma once

#include <any>
#include <vector>

class Arguments {
public:
    template<typename T> void add(const T& value) {
        args.emplace_back(value);
    }
    const std::any& operator[](size_t index) const;
    [[nodiscard]] size_t size() const;
    [[nodiscard]] const std::vector<std::any>& getAll() const;

private:
    std::vector<std::any> args;
};


