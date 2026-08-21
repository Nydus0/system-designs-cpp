//
// Created by Nydus0 on 21/08/2026.
//

#include "modules/generic_processor/InstanceProvider.hpp"

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
    COLOR_C,
    COLOR_D,
    COLOR_E
};

TEST(generic_processor, create_provider) {

    InstanceProvider<Color, ProcessorConcept, ProcessorSpec> processors;
    processors.addInstance<Color::COLOR_A>();
    processors.addInstance<Color::COLOR_C>();
    processors.addInstance<Color::COLOR_D, Color::COLOR_E>();

    auto* proc = processors.getInstance(Color::COLOR_A);

    ASSERT_NE(proc, nullptr);
    proc->process();

}


