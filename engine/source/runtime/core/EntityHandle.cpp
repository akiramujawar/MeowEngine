//
// Created by Akira Mujawar on 19/06/26.
//

#include "EntityHandle.hpp"

namespace MeowEngine::Runtime {

    EntityHandle::EntityHandle()
        : IsValid(false), Entity(Entity::INVALID), GUID(EntityID::INVALID)
    {}

    bool EntityHandle::operator==(const EntityHandle& handle) const {
        return GUID == handle.GUID;
    }

    bool EntityHandle::operator!=(const EntityHandle& handle) const {
        return GUID != handle.GUID;
    }

    EntityHandle EntityHandle::Create(const EntityID guid, const Runtime::Entity entity) {
        auto handle = EntityHandle();
        handle.GUID = guid;
        handle.Entity = entity;
        handle.IsValid = true;

        return handle;
    }

}
