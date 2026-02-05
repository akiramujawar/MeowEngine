//
// Created by Akira Mujawar on 30/08/24.
//

#include "collider_component.hpp"
#include "entt_reflection_wrapper.hpp"
#include <log.hpp>

using namespace MeowEngine::entity;

namespace MeowEngine {
    void entity::ColliderComponent::Reflect() {
        // TODO: Create a auto-reflection system. This will also solve dup reflections
        MeowEngine::Reflection.Reflect<BoxColliderData>();
        MeowEngine::Reflection.Reflect<SphereColliderData>();

        REGISTER_PROPERTY(ColliderComponent, Type, entity::ColliderType);
        REGISTER_POINTER(ColliderComponent, Data, entity::ColliderData*, true);
        REGISTER_POINTER(ColliderComponent, Body, physx::PxActor*, false);

        MeowEngine::Log("Reflected", "ColliderComponent");
    }

    ColliderComponent::ColliderComponent(entity::ColliderType inType, entity::ColliderData *inData) {
        Type = inType;
        Data = inData;
    }

    entity::ColliderType &ColliderComponent::GetType() {
        return Type;
    }

    physx::PxGeometry &ColliderComponent::GetGeometry() {
        return Data->GetGeometry();
    }

    void ColliderComponent::SetPhysicsBody(physx::PxActor *inActor) {
        Body = inActor;
    }
}