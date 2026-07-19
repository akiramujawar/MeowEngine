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
        if (IsSimulating) {
            World->Simulate(inFixedDeltaTime);
        }
    }

    void PhysicsSystem::StartSimulation() {
        IsSimulating = true;
    }

    void PhysicsSystem::StopSimulation() {
        // World->Destroy();
        IsSimulating = false;
    }

    void PhysicsSystem::FetchResult(PhysicsResult& result) {
        // TODO: when physics stop we need to clean buffers without requiring fetch
        // clean buffer data
        result.RigidBodies.clear();

        if (IsSimulating) {
            World->FetchResults(result);
        }
    }

    void PhysicsSystem::CreateWorld(std::unique_ptr<PhysicsWorldData> data) {
        World->Destroy();
        World->Create(*data);
    }

    void PhysicsSystem::DestroyWorld() {
        World->Destroy();
    }
}
