//
// Created by Nydus0 on 21/08/2026.
//

#pragma once

#include <memory>
#include <map>

//rule
template <typename T>
concept EnumType = std::is_enum_v<T>;

//model
template <EnumType Enum,
    template <typename> class Concept,
    template <typename, auto> class Spec>
class ProcessorRegistry {
public:
    virtual ~ProcessorRegistry() = default;

    template <Enum... Values>
    requires ((std::derived_from<Spec<Enum, Values>, Concept<Enum>>
        && std::default_initializable<Spec<Enum, Values>>)
        && ...)
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
