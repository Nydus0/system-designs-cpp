//
// Created by Nydus0 on 23/01/2026.
//

#pragma once

#include <gtest/gtest.h>

template <typename Func>
std::string captureCout(Func function) {
    testing::internal::CaptureStdout();
    function();
    return testing::internal::GetCapturedStdout();
}