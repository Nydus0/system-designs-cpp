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
    template <typename> class Base,
    template <typename, auto> class Spec>
class InstanceProvider {
public:
    virtual ~InstanceProvider() = default;

    template <Enum... Values>
    requires ((std::derived_from<Spec<Enum, Values>, Base<Enum>>
        && std::default_initializable<Spec<Enum, Values>>)
        && ...)
    void addInstance() {
        (instances.emplace(
            Values,
            std::make_unique<Spec<Enum, Values>>()
        ), ...);
    }

    [[nodiscard]] Base<Enum>* getInstance(Enum value) {
        auto it = instances.find(value);
        if (it == instances.end()) {
            return nullptr;
        }
        return it->second.get();
    }

private:
    std::map<Enum, std::unique_ptr<Base<Enum>>> instances;

};
