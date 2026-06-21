//
// Created by Akira Mujawar on 11/03/26.
//

#include <World.hpp>

#include "UUID.hpp"
// - essential components only -
// don't couple all components in world (identity / hierarchy / info are exceptions)
#include "IdentityComponent.hpp"
#include "hierarchy_component.hpp"
#include "info_component.hpp"

namespace MeowEngine::Asset {
    World::World()
        : ActiveCamera()
        , SkyBox()
    {}

    Runtime::EntityHandle World::AddEntity() {
        const auto id = Runtime::EntityID {Core::UUID::GenerateUUID()};
        return AddEntity(id);
    }

    Runtime::EntityHandle World::AddEntity(const Runtime::EntityID guid) {
        const auto entity = Registry.create();
        auto& identity = Registry.emplace<Runtime::IdentityComponent>(entity);
        auto& hierarchy = Registry.emplace<component::HierarchyComponent>(entity);
        auto& info = Registry.emplace<entity::InfoComponent>(entity);

        identity.Set(guid, entity);
        hierarchy.Self = identity.GetEntityHandle();
        info.SetName(String("New Entity"));

        return identity.GetEntityHandle();
    }

    Runtime::EntityHandle World::FindHandle(Runtime::EntityID guid) {
        const auto view = Registry.view<Runtime::IdentityComponent>();
        for (const auto entity : view) {
            const auto& identity = view.get<Runtime::IdentityComponent>(entity);
            if (identity.GetGUID() == guid) {
                return identity.GetEntityHandle();
            }
        }

        return Runtime::EntityHandle {};
    }

    bool World::Has(const Runtime::EntityHandle& handle) {
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
