//
// Created by Nydus0 on 21/08/2026.
//

#include "modules/instance_provider/InstanceProvider.hpp"

#include <gtest/gtest.h>

template <typename> class ProcessorConcept {
public:
    virtual ~ProcessorConcept() = default;
    virtual void process() = 0;
};

template <typename Enum, auto>
class ProcessorSpec : public ProcessorConcept<Enum> {
public:
    void process() override {}
};

enum class Color {
    COLOR_A,
    COLOR_B,
    COLOR_C,
    COLOR_D,
    COLOR_E
};

TEST(generic_processor, provider) {

    InstanceProvider<Color, ProcessorConcept, ProcessorSpec> processors;

    processors.addInstance<Color::COLOR_A>();
    //COLOR_B is intentionnaly not added
    processors.addInstance<Color::COLOR_C>();
    processors.addInstance<Color::COLOR_D, Color::COLOR_E>();

    auto* procA = processors.getInstance(Color::COLOR_A);
    auto* procB = processors.getInstance(Color::COLOR_B);
    auto* procC = processors.getInstance(Color::COLOR_C);
    auto* procD = processors.getInstance(Color::COLOR_D);
    auto* procE = processors.getInstance(Color::COLOR_E);

    ASSERT_NE(procA, nullptr);
    ASSERT_EQ(procB, nullptr);
    ASSERT_NE(procC, nullptr);
    ASSERT_NE(procD, nullptr);
    ASSERT_NE(procE, nullptr);

    procA->process();
}


