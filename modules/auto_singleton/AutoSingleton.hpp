//
// Created by Nydus0 on 18/07/2025.
//

#pragma once

#include <memory>
#include <mutex>

template <typename T> class AutoSingleton {
public:
    //delete special member functions
    AutoSingleton() = delete;
    ~AutoSingleton() = delete;
    AutoSingleton(const AutoSingleton&) = delete;
    AutoSingleton& operator=(const AutoSingleton&) = delete;

    //accessor
    static T& get() {
        std::call_once(initFlag, [](){ instance.reset(new T()); });
        return *instance;
    }

    //optional manual destruction
    static void destroy() { instance.reset(); }

private:
    static std::unique_ptr<T> instance;
    static std::once_flag initFlag;
};

//definition of static members
template <typename T> std::unique_ptr<T> AutoSingleton<T>::instance {nullptr};
template <typename T> std::once_flag AutoSingleton<T>::initFlag;
