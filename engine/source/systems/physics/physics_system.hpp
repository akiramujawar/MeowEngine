//
// Created by Akira Mujawar on 12/08/24.
//

#ifndef MEOWENGINE_PHYSICS_SYSTEM_HPP
#define MEOWENGINE_PHYSICS_SYSTEM_HPP

#include "entt_wrapper.hpp"

namespace MeowEngine::simulator {
    struct PhysicsSystem {
        virtual void Create() = 0;
        virtual void Update(float inFixedDeltaTime) = 0;

        virtual void AddRigidbody(entt::registry& pPhysicsRegistry, const entt::entity& pEntity) = 0;
        virtual void RemoveRigidbody(entt::registry& pPhysicsRegistry, const entt::entity& pEntity) = 0;
        virtual void SyncTransform(entt::registry& pPhysicsRegistry, const entt::entity& pEntity) = 0;

        virtual bool IsRigidbody(entt::registry& pPhysicsRegistry, const entt::entity& pEntity) = 0;
    };
}


#endif //MEOWENGINE_PHYSICS_SYSTEM_HPP
