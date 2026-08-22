//
// Created by Nydus0 on 21/08/2026.
//

#pragma once

#include <memory>
#include <map>

/**
 * @brief Concept restricting a type to enum types.
 *
 * Used by InstanceProvider to ensure that the key used to identify
 * instances is an enumeration.
 */
template <typename T>
concept EnumType = std::is_enum_v<T>;

/** -----------------------------------------------------------------------------
 * Provider Model
 * -----------------------------------------------------------------------------
 * @brief Stores and provides access to objects associated with enum values.
 *
 * InstanceProvider is responsible for creating and storing one instance of
 * each requested specialization of Spec, indexed by an enum value.
 *
 * @tparam Enum The enum type used to identify each instance.
 *
 * @tparam Base A class template representing the common base type of all instances.
 * It must have the form: template <typename> class Base;
 *
 * @tparam Spec A class template representing the concrete implementation associated with an enum value.
 * It must have the form: template <typename, auto> class Spec;
 * The first parameter is the enum type and the second parameter is the enum value.
 *
 * The provider owns all created instances through std::unique_ptr.
 */
template <EnumType Enum,
    template <typename> class Base,
    template <typename, auto> class Spec>
class InstanceProvider {
public:
    // When adding an instance, some constraints are enforced :
    // Spec must derive from Base & Spec must be default constructible
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

    //Returns a previously created instance
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
