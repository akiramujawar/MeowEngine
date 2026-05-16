//
// Created by Akira Mujawar on 11/03/26.
//

#include <World.hpp>

namespace MeowEngine::Runtime {
    entt::entity World::AddEntity() {
        return Registry.create();
    }
}