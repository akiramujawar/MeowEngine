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
        for (auto& collider : context.Colliders) {

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
    }

    void PhysXWorld::Simulate(float inFixedDeltaTime) const {
        PT_PROFILE_SCOPE;
        gScene->simulate(inFixedDeltaTime);
    }

    void PhysXWorld::FetchResults() const {
        PT_PROFILE_SCOPE;
        gScene->fetchResults(true);
    }

    void PhysXWorld::AddPlaneCollider(const Transform& worldTransform) const {
        physx::PxPlaneGeometry geometry = physx::PxPlaneGeometry();

        // material =>

        // setup transform
        physx::PxTransform transform;
        const auto position = worldTransform.GetPosition();
        const auto rotation = worldTransform.GetQuaternion();
        transform.p = physx::PxVec3(position.X, position.Y, position.Z);
        transform.q = physx::PxQuat(rotation.X, rotation.Y, rotation.Z, rotation.W);

        AddRigidStatic(&geometry, transform);
    }

    void PhysXWorld::AddRigidStatic(const physx::PxGeometry* geometry, const physx::PxTransform& transform) const {
        // setup actor
        physx::PxMaterial* material = gPhysics->createMaterial(1, 1, 1);
        physx::PxRigidStatic* actor = physx::PxCreateStatic(*gPhysics, transform, *geometry, *material);

        // setup shape
        physx::PxShape* shape = gPhysics->createShape(*geometry, *material);
        actor->attachShape(*shape);
    }

    void PhysXWorld::AddRigidbody() {

        // physx::PxTransform physicsTransform(physx::PxVec3(transform.Position.X,transform.Position.Y,transform.Position.Z));
        // physx::PxGeometry& geometry = collider.GetGeometry(); // has scale data as well
        // physx::PxShape* shape = gPhysics->createShape(geometry, *gPhysics->createMaterial(0.5f, 0.5f, 0.6f));
        //
        // physx::PxRigidDynamic* actor = physx::PxCreateDynamic(*gPhysics, physicsTransform, geometry, *gPhysics->createMaterial(0.5f, 0.5f, 0.6f), density);
        // actor->attachShape(colliderData.GetShape());
        //
        // gScene->addActor(*actor);
    }
}
