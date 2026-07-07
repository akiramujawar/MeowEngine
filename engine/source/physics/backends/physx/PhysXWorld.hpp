//
// Created by Akira Mujawar on 12/08/24.
//

#ifndef MEOWENGINE_PHYSX_SYSTEM_HPP
#define MEOWENGINE_PHYSX_SYSTEM_HPP

#include <unordered_map>

#include "Math.hpp"
#include "PhysXRigidbody.hpp"


namespace MeowEngine::Physics {
    /**
     * Reads from main system physics snapshot
     * Prepares physics results (to be utilised by main system)
     * Emits events like collisions
     */
    class PhysXWorld {
    public:
        PhysXWorld();
        ~PhysXWorld();

        void Create(const PhysicsWorldData& context);
        void Destroy();

        void Simulate(float inFixedDeltaTime) const;
        void FetchResults() const;

        void AddRigidbody();
        void AddCollider();

        void RemoveRigidbody();
        void RemoveCollider();

    private:
        // <EntityID, Rigidbody> map
        // rigidbody contains physX actor?
        // we need to map shapes materials with editor
        // we create PhysXActor which contains
        // then essentially
        // <EntityID, PhysXActor>
        // PhysXActor > physx::actor
        // each component has guid thus we track same
        // with PhysXShape, PhysXMaterial etc...
        // lets start with something simple
        // on play -> create physxWorld
        // does physics uses runtime or runtime use physics
        // since we want physics to be separate module
        // runtime depends upon physics

        std::unordered_map<uint32_t, PhysXRigidbody> Actors;



        void AddPlaneCollider(const Transform& worldTransform) const;
        void AddCubeCollider();
        void AddSphereCollider();

        void RemovePlaneCollider();


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


#endif //MEOWENGINE_PHYSX_SYSTEM_HPP
