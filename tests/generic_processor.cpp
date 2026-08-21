//
// Created by Nydus0 on 21/08/2026.
//

#include "modules/generic_processor/GenericProcessor.hpp"

#include <gtest/gtest.h>

enum class Color {
    COLOR_A,
    COLOR_B,
    COLOR_C
};

using ColorModel = ProcessorModel<
    Color,
    Color::COLOR_A,
    Color::COLOR_B,
    Color::COLOR_C
>;

ColorModel model;

TEST(generic_processor, create_model) {
    ProcessorRegistry<Color> registry;
    registry.addProcessor<Color::COLOR_A>();
    registry.addProcessor<Color::COLOR_C>();

    auto proc = registry.getProcessor(Color::COLOR_A);
    proc->process();

}


