//
// Created by Akira Mujawar on 12/08/24.
//

#ifndef MEOWENGINE_PHYSX_PHYSICS_SYSTEM_HPP
#define MEOWENGINE_PHYSX_PHYSICS_SYSTEM_HPP



#include "PhysicsSystem.hpp"
#include "PxPhysicsAPI.h"
#include "entt.hpp"

namespace MeowEngine::simulator {
    struct PhysXPhysicsSystem {
        PhysXPhysicsSystem();
        ~PhysXPhysicsSystem();

        void Create() ;
        void Update(float inFixedDeltaTime) ;

        void AddRigidbody(entt::registry& pPhysicsRegistry, const entt::entity& pEntity) ;
        void RemoveRigidbody(entt::registry& pPhysicsRegistry, const entt::entity& pEntity) ;
        void SyncTransform(entt::registry& pPhysicsRegistry, const entt::entity& pEntity) ;

        bool IsRigidbody(entt::registry& pPhysicsRegistry, const entt::entity& pEntity) ;

    private:
        // PhysX Foundation
        physx::PxDefaultAllocator gAllocator;
        physx::PxDefaultErrorCallback gErrorCallback;
        physx::PxFoundation* gFoundation = nullptr;
        physx::PxPhysics* gPhysics = nullptr;

        // PhysX Scene Items
        physx::PxScene* gScene;
//        physx::PxTransform testTransform;
//        physx::PxRigidDynamic* body;
    };
}

#endif //MEOWENGINE_PHYSX_PHYSICS_SYSTEM_HPP
