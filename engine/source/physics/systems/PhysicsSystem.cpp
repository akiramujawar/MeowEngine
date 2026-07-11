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
    }

    void PhysicsSystem::StartSimulation() {

    }

    void PhysicsSystem::StopSimulation() {
        // World->Destroy();
    }

    void PhysicsSystem::FetchResult(PhysicsResult& result) {
        World->FetchResults(result);
    }

    void PhysicsSystem::CreateWorld(std::unique_ptr<PhysicsWorldData> data) {
        World->Destroy();
        World->Create(*data);
    }

    void PhysicsSystem::DestroyWorld() {
        World->Destroy();
    }
}
