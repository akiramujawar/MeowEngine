//
// Created by Akira Mujawar on 12/08/24.
//

#ifndef MEOWENGINE_PHYSICS_SYSTEM_HPP
#define MEOWENGINE_PHYSICS_SYSTEM_HPP

#include <PhysicsWorld.hpp>
#include "PxPhysicsAPI.h"
#include "Math.hpp"

namespace MeowEngine::Physics {
    /**
     * Reads from main system physics snapshot
     * Prepares physics results (to be utilised by main system)
     * Emits events like collisions
     */
    class PhysicsSystem {
    public:
        PhysicsSystem();
        ~PhysicsSystem();
        PhysicsWorld World;

        void Create();
        void Destroy() const;

        void Step(float inFixedDeltaTime) const;

        void AddPlaneCollider(const Transform& worldTransform) const;
        void AddCubeCollider();
        void AddSphereCollider();

        void RemovePlaneCollider();

        void CreateCubeGeometry();
        void CreateSphereGeometry();

        void RemoveCollider();
        void AddRigidbody();
        void RemoveRigidbody();

        bool IsRigidbody();

    private:
        void AddRigidStatic(const physx::PxGeometry* geometry, const physx::PxTransform& transform) const;

    private:
        // PhysX Foundation
        physx::PxDefaultAllocator gAllocator;
        physx::PxDefaultErrorCallback gErrorCallback;
        physx::PxFoundation* gFoundation = nullptr;
        physx::PxPhysics* gPhysics = nullptr;

        // PhysX Scene Items
        physx::PxScene* gScene = nullptr;
    };
}


#endif //MEOWENGINE_PHYSICS_SYSTEM_HPP
