//
// Created by Akira Mujawar on 03/07/26.
//

#include "PhysicsSystem.hpp"

#include "PhysXWorld.hpp"

namespace MeowEngine::Physics {

    void PhysicsSystem::SetPhysics(PhysicsType type) {
        World = std::make_unique<PhysXWorld>();
    }

    void PhysicsSystem::Step(float inFixedDeltaTime) const {
        World->Simulate(inFixedDeltaTime);
        World->FetchResults();
    }
}
