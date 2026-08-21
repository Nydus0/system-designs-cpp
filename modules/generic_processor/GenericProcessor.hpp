//
// Created by Nydus0 on 21/08/2026.
//

#pragma once

#include <memory>
#include <map>

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

template <typename Enum> class ProcessorRegistry {
public:
    virtual ~ProcessorRegistry() = default;

    template <Enum... Values> void addProcessor();
    ProcessorConcept<Enum>* getProcessor(Enum value);

private:
    std::map<Enum, std::unique_ptr<ProcessorConcept<Enum>>> processors;

};

template <typename Enum>
template <Enum... Values>
void ProcessorRegistry<Enum>::addProcessor() {
    (processors.emplace(
        Values,
        std::make_unique<ProcessorSpec<Enum, Values>>()
    ), ...);
}

template <typename Enum>
[[nodiscard]] ProcessorConcept<Enum>* ProcessorRegistry<Enum>::getProcessor(Enum value) {
    auto it = processors.find(value);
    if (it == processors.end()) {
        return nullptr;
    }
    return it->second.get();
}

template <typename Enum, Enum... Values>
class ProcessorModel {
public:
    ProcessorModel() {
        registry.template addProcessor<Values...>();
    }

private:
    ProcessorRegistry<Enum> registry;
};
