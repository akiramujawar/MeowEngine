//
// Created by Akira Mujawar on 11/03/26.
//

#include <World.hpp>

// - essential components only -
// don't couple all components in world (identity / hierarchy / info are exceptions)
#include <IdentityComponent.hpp>

namespace MeowEngine::Asset {
    entt::entity World::AddEntity() {
        return Registry.create();
    }

    entt::entity World::GetEntity(uint32_t guid) {
        auto view = Registry.view<Runtime::IdentityComponent>();
        for (auto entity : view) {
            auto&& identity = view.get<Runtime::IdentityComponent>(entity);

            if (identity.GetGUID() == guid) {
                return entity;
            }
        }

        return entt::null;
    }
}
