//
// Created by Nydus0 on 21/08/2026.
//

#include "modules/generic_processor/GenericProcessor.hpp"

#include <gtest/gtest.h>

template <typename Enum> class ProcessorConcept {
public:
    virtual ~ProcessorConcept() = default;
    virtual void process() = 0;
};

template <typename Enum, Enum Value>
class ProcessorSpec : public ProcessorConcept<Enum> {
public:
    void process() override {
        // Value is available at compile time
    }
};

enum class Color {
    COLOR_A,
    COLOR_B,
    COLOR_C
};

using ColorModel = ProcessorModel<
    Color,
    ProcessorConcept,
    ProcessorSpec,
    Color::COLOR_A,
    Color::COLOR_B,
    Color::COLOR_C
>;

TEST(generic_processor, create_model) {
    ProcessorRegistry<Color, ProcessorConcept, ProcessorSpec> registry;
    registry.addProcessor<Color::COLOR_A>();
    registry.addProcessor<Color::COLOR_C>();

    const auto proc = registry.getProcessor(Color::COLOR_A);
    proc->process();

}


