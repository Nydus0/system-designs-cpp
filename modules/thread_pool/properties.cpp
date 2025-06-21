//
// Created by Nydus0 on 21/06/2025.
//

#include "modules/thread_pool/properties.hpp"

#include <iostream>

int print_sum(int a, int b) {
    return a + b;
}

int add(int a, int b) {
    return a + b;
}

std::string greet(const std::string& name) {
    return "Hello, " + name;
}

std::string myFunction(int x, double y, const std::string& z) {
    return "Result: " + std::to_string(x + int(y)) + " " + z;
}