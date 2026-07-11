//
// Created by Akira Mujawar on 11/07/26.
//

#include "PhysicsSynchronizer.hpp"

#include "Transform3DComponent.hpp"

namespace MeowEngine::Runtime {

    void PhysicsSynchronizer::ApplyResult(Asset::World& world, const Physics::PhysicsResult& result) {
        // auto& ecs = world->GetRegistry();

        for (auto& rigidbody : result.RigidBodies) {
            auto id = EntityID {rigidbody.ObjectID};
            auto handle = world.GetHandle(id);

            auto& transform = world.GetComponent<Transform3DComponent>(handle).GetRootTransform();
            transform.SetPosition(rigidbody.Position);
            transform.SetRotation(rigidbody.Quaternion);
        }
    }

}