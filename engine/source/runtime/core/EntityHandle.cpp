//
// Created by Akira Mujawar on 19/06/26.
//

#include "EntityHandle.hpp"

#include "reflection_macro_wrapper.hpp"

namespace MeowEngine::Runtime {

    void EntityHandle::Reflect() {
        REGISTER_PROPERTY(EntityHandle, IsValid, bool, true, true);
        // REGISTER_PROPERTY(EntityHandle, Entity, bool, true, true);
        REGISTER_PROPERTY(EntityHandle, GUID, EntityID, true, true);
    }

    EntityHandle::EntityHandle()
        : IsValid(false), Entity(Entity::INVALID), GUID(EntityID::INVALID)
    {}

    bool EntityHandle::operator==(const EntityHandle& handle) const {
        return GUID == handle.GUID;
    }

    bool EntityHandle::operator!=(const EntityHandle& handle) const {
        return GUID != handle.GUID;
    }

    EntityHandle EntityHandle::Empty(const EntityID guid) {
        auto handle = EntityHandle();
        handle.GUID = guid;
        handle.IsValid = false;

        return handle;
    }

    EntityHandle EntityHandle::Create(const EntityID guid, const Runtime::Entity entity) {
        auto handle = EntityHandle();
        handle.GUID = guid;
        handle.Entity = entity;
        handle.IsValid = true;

        return handle;
    }

    EntityHandle EntityHandle::Invalid() {
        return EntityHandle();
    }

    void EntityHandle::SetEntity(Runtime::Entity entity) {
        Entity = entity;
    }
}
