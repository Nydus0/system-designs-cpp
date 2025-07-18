//
// Created by Nydus0 on 18/07/2025.
//

#pragma once

#include <iostream>

class MyService {
public:
    MyService()  { std::cout << "MyService created\n"; }
    ~MyService() { std::cout << "MyService destroyed\n"; }

    void run() { std::cout << "Running service...\n"; }
};