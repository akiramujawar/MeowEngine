//
// Created by Akira Mujawar on 01/08/24.
//

#include "InfoComponent.hpp"
#include <log.hpp>
#include "reflection_macro_wrapper.hpp"

namespace MeowEngine::Runtime {
    void MeowEngine::Runtime::InfoComponent::Reflect() {
        REGISTER_PROPERTY(InfoComponent, Name, String, true, true);
    }

    MeowEngine::Runtime::InfoComponent::InfoComponent() {}

    MeowEngine::Runtime::InfoComponent::InfoComponent(std::string name)
        : Name(name)
    {}

    void InfoComponent::SetName(const String& name) {
        Name = name;
    }

    String InfoComponent::GetName() const {
        return Name;
    }
}