//
// Created by Nydus0 on 21/08/2026.
//

#pragma once

#include <memory>
#include <map>

template <
    typename Enum,
    template <typename> class Concept,
    template <typename, Enum> class Spec
> class ProcessorRegistry {
public:
    virtual ~ProcessorRegistry() = default;

    template <Enum... Values>
    void addProcessor() {
        (processors.emplace(
            Values,
            std::make_unique<Spec<Enum, Values>>()
        ), ...);
    }

    [[nodiscard]] Concept<Enum>* getProcessor(Enum value) {
        auto it = processors.find(value);
        if (it == processors.end()) {
            return nullptr;
        }
        return it->second.get();
    }

private:
    std::map<Enum, std::unique_ptr<Concept<Enum>>> processors;

};

template <
    typename Enum,
    template <typename> class Concept,
    template <typename, Enum> class Spec,
    Enum... Values
>
class ProcessorModel {
public:
    ProcessorModel() { registry.template addProcessor<Values...>(); }

    [[nodiscard]]
    Concept<Enum>* getProcessor(Enum value)
    {
        return registry.getProcessor(value);
    }

private:
    ProcessorRegistry<Enum, Concept, Spec> registry;
};
