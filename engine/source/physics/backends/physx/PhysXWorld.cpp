//
// Created by Akira Mujawar on 12/08/24.
//

#include <PhysXWorld.hpp>

#include "log.hpp"


namespace MeowEngine::Physics {
    PhysXWorld::PhysXWorld() {
        MeowEngine::Log("Physics", "Constructed");

        // create physics
        gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);
        gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, physx::PxTolerancesScale(), true, nullptr);

        // create description
        physx::PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
        sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
        sceneDesc.cpuDispatcher = physx::PxDefaultCpuDispatcherCreate(0); // can't have more than 1 thread here for web
        sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;

        // create scene
        gScene = gPhysics->createScene(sceneDesc);
    }

    PhysXWorld::~PhysXWorld() {
        MeowEngine::Log("`", "Destructed");

        gScene->release();
        gPhysics->release();
        gFoundation->release();
    }

    void PhysXWorld::Create(const PhysicsWorldData& context) {
        for (auto& material : context.Materials) {
            AddPhysicsMaterial(material);
        }

        for (auto& collider : context.Colliders) {
            AddCollider(collider);
        }

        for (auto& rigidbody : context.RigidBodies) {
            AddRigidbody(rigidbody);
        }
    }

    void PhysXWorld::Destroy() {
        for (auto& [key, value] : RigidBodies) {
            gScene->removeActor(*value.Rigidbody);
            value.Rigidbody->release();
        }

        for (auto& [key, value]: Colliders) {
            value.Collider->release();
        }

        for (auto& [key, value]: Materials) {
            value.Material->release();
        }

        RigidBodies.clear();
        Colliders.clear();
        Materials.clear();
    }

    void PhysXWorld::Simulate(float inFixedDeltaTime) const {
        PT_PROFILE_SCOPE;
        gScene->simulate(inFixedDeltaTime);
    }

    void PhysXWorld::FetchResults() const {
        PT_PROFILE_SCOPE;
        gScene->fetchResults(true);
    }

    void PhysXWorld::AddPhysicsMaterial(const PhysicsMaterial& data) {
        if (Materials.find(data.ObjectID) != Materials.end()) {
            return;
        }

        PhysXMaterial material {};
        material.ObjectID = data.ObjectID;
        material.Material = gPhysics->createMaterial(data.StaticFriction, data.DynamicFriction, data.Restitution);

        Materials.emplace(material.ObjectID, material);
    }

    void PhysXWorld::AddCollider(const Collider& data) {
        // if material exists we create collider
        // TODO: later if material isn't there we create a dummy one
        auto iterator = Materials.find(data.MaterialID);
        if (iterator != Materials.end()) {
            auto material = iterator->second;

            PhysXCollider collider {data.ObjectID, data.Type, nullptr, data.MaterialID};

            switch (data.Type) {
                case ColliderType::BOX: {
                    auto geometry = physx::PxBoxGeometry();
                    collider.Collider = gPhysics->createShape(geometry, *Materials[data.MaterialID].Material);
                    break;
                }
                case ColliderType::SPHERE: {
                    auto geometry = physx::PxSphereGeometry();
                    collider.Collider = gPhysics->createShape(geometry, *Materials[data.MaterialID].Material);

                    break;
                }
                case ColliderType::CAPSULE: {
                    auto geometry = physx::PxCapsuleGeometry();
                    collider.Collider = gPhysics->createShape(geometry, *Materials[data.MaterialID].Material);

                    break;
                }
                case ColliderType::MESH: {
                    // auto geometry = physx::PxConvexMeshGeometry();
                    // collider.Collider = gPhysics->createShape(geometry, *Materials[data.MaterialID].Material);

                    break;
                }
            }

            Colliders.emplace(data.ObjectID, collider);
        }
    }

    void PhysXWorld::AddRigidbody(const Rigidbody& data) {
        switch (data.Type) {
            case RigidbodyType::STATIC:
                AddRigidStatic(data);

                break;
            case RigidbodyType::DYNAMIC:
                AddRigidDynamic(data);

                break;
            case RigidbodyType::KINEMATIC:
                break;
        }


        // physx::PxTransform physicsTransform(physx::PxVec3(transform.Position.X,transform.Position.Y,transform.Position.Z));
        // physx::PxGeometry& geometry = collider.GetGeometry(); // has scale data as well
        // physx::PxShape* shape = gPhysics->createShape(geometry, *gPhysics->createMaterial(0.5f, 0.5f, 0.6f));
        //
        // physx::PxRigidDynamic* actor = physx::PxCreateDynamic(*gPhysics, physicsTransform, geometry, *gPhysics->createMaterial(0.5f, 0.5f, 0.6f), density);
        // actor->attachShape(colliderData.GetShape());
        //
        // gScene->addActor(*actor);
    }

    void PhysXWorld::AddRigidStatic(const Rigidbody& data) {
        PhysXRigidbody rigidbody = {data.ObjectID, data.Type, nullptr};
        rigidbody.Rigidbody = gPhysics->createRigidStatic(physx::PxTransform());

        RigidBodies.emplace(data.ObjectID, rigidbody);
        AttachColliders(data.ObjectID, data.ColliderIDs);
    }

    void PhysXWorld::AddRigidDynamic(const Rigidbody& data) {
        PhysXRigidbody rigidbody = {data.ObjectID, data.Type, nullptr};
        rigidbody.Rigidbody = gPhysics->createRigidDynamic(physx::PxTransform());

        RigidBodies.emplace(data.ObjectID, rigidbody);
        AttachColliders(data.ObjectID, data.ColliderIDs);
    }

    void PhysXWorld::AttachColliders(uint64_t rigidbodyID, const std::vector<uint64_t>& colliderIDs) {
        for (auto id : colliderIDs) {
            auto& rigidbody = RigidBodies[rigidbodyID];
            rigidbody.ColliderIDs.push_back(id);
            rigidbody.Rigidbody->attachShape(*Colliders[id].Collider);
        }
    }
}
