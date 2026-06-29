//
// Created by Akira Mujawar on 11/03/26.
//

#include <World.hpp>

#include "UUID.hpp"
// - essential components only -
// don't couple all components in world (identity / hierarchy / info are exceptions)
#include "IdentityComponent.hpp"
#include "HierarchyComponent.hpp"
#include "InfoComponent.hpp"

namespace MeowEngine::Asset {
    World::World()
        : ActiveCamera()
        , SkyBox() {
        // NOTE: create a invalid entity (default: Entity::INVALID
        // as Registry creates auto creates entity with id = 0
        auto entity = Registry.create();
    }

    Runtime::EntityHandle World::AddEntity() {
        const auto id = Runtime::EntityID {Core::UUID::GenerateUUID()};
        return AddEntity(id);
    }

    Runtime::EntityHandle World::AddEntity(const Runtime::EntityID guid) {
        const auto entity = Registry.create();
        auto& identity = Registry.emplace<Runtime::IdentityComponent>(entity);
        auto& hierarchy = Registry.emplace<Runtime::HierarchyComponent>(entity);
        auto& info = Registry.emplace<Runtime::InfoComponent>(entity);

        identity.Set(guid, entity);
        hierarchy.Self = identity.GetEntityHandle();
        info.SetName(String("New Entity"));

        RuntimeEntityMap.try_emplace(guid, hierarchy.Self);

        return identity.GetEntityHandle();
    }

    Runtime::EntityHandle World::GetHandle(Runtime::EntityID guid) {
        auto iterator = RuntimeEntityMap.find(guid);
        if (iterator != RuntimeEntityMap.end()) {
            return iterator->second;
        }

        return Runtime::EntityHandle::Invalid();
    }

    bool World::HasEntity(const Runtime::EntityHandle& handle) {
        const auto view = Registry.view<Runtime::IdentityComponent>();
        for (const auto entity : view) {
            const auto& identity = view.get<Runtime::IdentityComponent>(entity);
            if (identity.GetGUID() == handle.GetGUID()) {
                return true;
            }
        }

        return false;
    }

}
