//
// Created by Akira Mujawar on 15/03/26.
//

#include <IdentityComponent.hpp>
#include <UUID.hpp>

namespace MeowEngine::Runtime {
    void IdentityComponent::Reflect() {
        REGISTER_PROPERTY(IdentityComponent, Handle, EntityHandle, false, false)
    }

    IdentityComponent::IdentityComponent() : Handle() {}

    void IdentityComponent::Set(const EntityID guid, const Entity entity) {
        Handle = EntityHandle::Create(guid, entity);
    }

    void IdentityComponent::Set(EntityHandle entity) {
        Handle = entity;
    }

}
