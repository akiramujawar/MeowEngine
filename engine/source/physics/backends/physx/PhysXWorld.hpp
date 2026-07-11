//
// Created by Akira Mujawar on 12/08/24.
//

#ifndef MEOWENGINE_PHYSX_SYSTEM_HPP
#define MEOWENGINE_PHYSX_SYSTEM_HPP

#include <unordered_map>

#include "Math.hpp"

#include "PhysXRigidbody.hpp"
#include "PhysXCollider.hpp"
#include "PhysXMaterial.hpp"

#include "PhysicsWorldData.hpp"

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

        void AddPhysicsMaterial(const PhysicsMaterial& data);
        void AddCollider(const Collider& data);
        void AddRigidbody(const Rigidbody& data);

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


        void AddPlaneCollider(const Transform& worldTransform) const;
        void AddCubeCollider();
        void AddSphereCollider();

        void RemovePlaneCollider();


        bool IsRigidbody();

    private:
        void AddRigidStatic(const Rigidbody& data);
        void AddRigidDynamic(const Rigidbody& data);
        void AttachColliders(uint64_t rigidbodyID, const std::vector<uint64_t>& colliderIDs);

    private:
        // PhysX Foundation
        physx::PxDefaultAllocator gAllocator;
        physx::PxDefaultErrorCallback gErrorCallback;
        physx::PxFoundation* gFoundation = nullptr;
        physx::PxPhysics* gPhysics = nullptr;

        // PhysX Scene Items
        physx::PxScene* gScene = nullptr;

    private:
        // TODO: later create object id
        // & rigidbody handle etc...
        // TODO: later implement AOS inside physics
        std::unordered_map<uint64_t, PhysXRigidbody> RigidBodies;
        std::unordered_map<uint64_t, PhysXCollider> Colliders;
        std::unordered_map<uint64_t, PhysXMaterial> Materials;
    };
}


#endif //MEOWENGINE_PHYSX_SYSTEM_HPP
