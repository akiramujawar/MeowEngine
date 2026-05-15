//
// Created by Akira Mujawar on 01/08/24.
//

#include "info_component.hpp"
#include <log.hpp>
#include "reflection_macro_wrapper.hpp"

namespace MeowEngine::entity {
    void MeowEngine::entity::InfoComponent::Reflect() {
        REGISTER_PROPERTY(InfoComponent, Name, String, true, true);
    }

    MeowEngine::entity::InfoComponent::InfoComponent() {}

    MeowEngine::entity::InfoComponent::InfoComponent(std::string name)
    : Name(name) {}

    void InfoComponent::SetName(const String& name) {
        Name = name;
    }

    String InfoComponent::GetName() const {
        return Name;
    }
}

//int MeowEngine::entity::InfoComponent::s_GetNewId() {
//    return s_IdCounter++;
//}

//int MeowEngine::entity::InfoComponent::s_IdCounter = 0;