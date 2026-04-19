//
// Created by Akira Mujawar on 12/08/24.
//

#ifndef MEOWENGINE_PHYSICS_SYSTEM_HPP
#define MEOWENGINE_PHYSICS_SYSTEM_HPP

#include "entt.hpp"

#include <double_buffer.hpp>

#include <PhysicsWorld.hpp>
#include <PhysicsResult.hpp>


namespace MeowEngine::Runtime::Systems {
    /**
     * Reads from main system physics snapshot
     * Prepares physics results (to be utilised by main system)
     * Emits events like collisions
     */
    struct PhysicsSystem {
        PhysicsWorld World;
        DoubleBuffer<PhysicsResult> Result;

        void Step();


        virtual void Create() {};
        virtual void Update(float inFixedDeltaTime) {};

        virtual void AddRigidbody(entt::registry& pPhysicsRegistry, const entt::entity& pEntity) {};
        virtual void RemoveRigidbody(entt::registry& pPhysicsRegistry, const entt::entity& pEntity) {};
        virtual void SyncTransform(entt::registry& pPhysicsRegistry, const entt::entity& pEntity) {};

        virtual bool IsRigidbody(entt::registry& pPhysicsRegistry, const entt::entity& pEntity) {};
    };
}


#endif //MEOWENGINE_PHYSICS_SYSTEM_HPP
