//
// Created by Akira Mujawar on 12/08/24.
//

#include <log.hpp>
#include "physx_physics_system.hpp"

#include <transform3d_component.hpp>
#include <rigidbody_component.hpp>
#include <collider_component.hpp>

using namespace MeowEngine::entity;

MeowEngine::simulator::PhysXPhysicsSystem::PhysXPhysicsSystem() {
    gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);
    gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, physx::PxTolerancesScale(), true, nullptr);

    // create scene
    physx::PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
    sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
    sceneDesc.cpuDispatcher = physx::PxDefaultCpuDispatcherCreate(0); // can't have more than 1 thread here for web
    sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;

    gScene = gPhysics->createScene(sceneDesc);

    MeowEngine::Log("Physics", "Constructed");
}

MeowEngine::simulator::PhysXPhysicsSystem::~PhysXPhysicsSystem() {
    gScene->release();
    gPhysics->release();
    gFoundation->release();

    MeowEngine::Log("Physics", "Destructed");
}

void MeowEngine::simulator::PhysXPhysicsSystem::Create() {


    physx::PxRigidStatic* groundPlane = physx::PxCreatePlane(*gPhysics, physx::PxPlane(0,1,0,0), *gPhysics->createMaterial(1,1,1));
    gScene->addActor(*groundPlane);

//groundPlane->getGlobalPose()
  //  physx::PxShape* test =  gPhysics->createShape(physx::PxBoxGeometry(), *gPhysics->createMaterial(0.5f, 0.5f, 0.6f));
  //  physx::PxCreateStatic(*gPhysics, physx::PxTransform(), *test);

//    physx::PxReal density = 1.0f;
//     testTransform = physx::PxTransform(physx::PxVec3(0,10,0));
//    physx::PxBoxGeometry geometry(physx::PxVec3(0.5f, 0.5f, 0.5f));
//    body = physx::PxCreateDynamic(*gPhysics, testTransform, geometry, *gPhysics->createMaterial(0.5f, 0.5f, 0.6f), density);
//
//    gScene->addActor(*body);



//    gScene->removeActor(*body);
}

void MeowEngine::simulator::PhysXPhysicsSystem::Update(float inFixedDeltaTime) {
  //  for(int i = 0 ;i < 1000; ++i)
  //  {

  // MeowEngine::Log("", std::to_string(body->getGlobalPose().p.y));
        gScene->simulate(inFixedDeltaTime);
        gScene->fetchResults(true);
  //  }
}

void MeowEngine::simulator::PhysXPhysicsSystem::AddRigidbody(entt::registry& pPhysicsRegistry, const entt::entity& pEntity ) {
    // From all transform rigidbody, collider, get the new entity and add rigidbody to it.
    // quiet complex in runtime as we do a query check
    // also we currently only add rigidbody when we have all 3
    // that prevents us from adding extra colliders essentially leading to create a duplicate rigidbody with following logic
    if(pPhysicsRegistry.all_of<entity::Transform3DComponent, entity::ColliderComponent, entity::RigidbodyComponent>(pEntity)) {
        auto [transform, collider, rigidbody] =  pPhysicsRegistry.get<entity::Transform3DComponent, entity::ColliderComponent, entity::RigidbodyComponent>(pEntity);

        physx::PxTransform physicsTransform(physx::PxVec3(transform.Position.X,transform.Position.Y,transform.Position.Z));

        entity::ColliderShapeBase& colliderData = collider.GetColliderData();
        colliderData.CreateGeometry();
        colliderData.CreateMaterial(gPhysics);
        colliderData.CreateShape(gPhysics);


//        physx::PxGeometry& geometry = collider.GetGeometry(); // has scale data as well
//        physx::PxShape* shape = gPhysics->createShape(geometry, *gPhysics->createMaterial(0.5f, 0.5f, 0.6f));

        // transform has rotation and position data
//        physx::PxRigidDynamic* actor = physx::PxCreateDynamic(*gPhysics, physicsTransform, geometry, *gPhysics->createMaterial(0.5f, 0.5f, 0.6f), density);
        physx::PxRigidDynamic* actor = gPhysics->createRigidDynamic(physicsTransform);
        actor->attachShape(colliderData.GetShape());

        rigidbody.SetPhysicsBody(actor);
        collider.SetPhysicsBody(actor);

        physx::PxRigidBodyExt::updateMassAndInertia(*actor,1.0f);

        gScene->addActor(*actor);
    }
}

void MeowEngine::simulator::PhysXPhysicsSystem::RemoveRigidbody(entt::registry& pPhysicsRegistry, const entt::entity& pEntity) {
    if(pPhysicsRegistry.all_of<entity::RigidbodyComponent>(pEntity)) {
        auto rigidbody = pPhysicsRegistry.get<entity::RigidbodyComponent>(pEntity);
        gScene->removeActor(*rigidbody.GetPhysicsBody());
    }
}

void MeowEngine::simulator::PhysXPhysicsSystem::SyncTransform(entt::registry& pPhysicsRegistry, const entt::entity& pEntity) {
    if(pPhysicsRegistry.all_of<entity::Transform3DComponent, entity::RigidbodyComponent>(pEntity)) {
        auto [transform, rigidbody] = pPhysicsRegistry.get<entity::Transform3DComponent, entity::RigidbodyComponent>(pEntity);
        rigidbody.OverrideTransform(transform);
    }
}

bool MeowEngine::simulator::PhysXPhysicsSystem::IsRigidbody(entt::registry& pPhysicsRegistry, const entt::entity& pEntity) {
    auto view = pPhysicsRegistry.view<entity::Transform3DComponent, entity::RigidbodyComponent>();

    return view.contains(pEntity);
}
