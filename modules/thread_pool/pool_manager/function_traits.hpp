//
// Created by Nydus0 on 06/07/2025.
//

#pragma once

#include <functional>

template<typename T>
struct function_traits;

// Function pointer
template<typename R, typename... Args>
struct function_traits<R(*)(Args...)> {
    using return_type = R;
    using args_tuple = std::tuple<Args...>;
};

// std::function
template<typename R, typename... Args>
struct function_traits<std::function<R(Args...)>> {
    using return_type = R;
    using args_tuple = std::tuple<Args...>;
};

// Lambda or functor
template<typename F>
struct function_traits : function_traits<decltype(&F::operator())> {};

// Member function pointer
template<typename C, typename R, typename... Args>
struct function_traits<R(C::*)(Args...) const> {
    using return_type = R;
    using args_tuple = std::tuple<Args...>;
};
