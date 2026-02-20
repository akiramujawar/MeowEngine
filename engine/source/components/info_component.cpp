//
// Created by Akira Mujawar on 01/08/24.
//

#include "info_component.hpp"
#include <log.hpp>
#include "reflection_macro_wrapper.hpp"

void MeowEngine::entity::InfoComponent::Reflect() {
    REGISTER_PROPERTY(InfoComponent, Name, MeowEngine::PString, true, true);
}

MeowEngine::entity::InfoComponent::InfoComponent(std::string name)
: Name(name)
//, Id(MeowEngine::entity::InfoComponent::s_GetNewId())
{}

//int MeowEngine::entity::InfoComponent::s_GetNewId() {
//    return s_IdCounter++;
//}

//int MeowEngine::entity::InfoComponent::s_IdCounter = 0;