//
// Created by Akira Mujawar on 30/08/24.
//

#include "collider_component.hpp"
#include "reflection_macro_wrapper.hpp"
#include <log.hpp>

using namespace MeowEngine::entity;

namespace MeowEngine {
    void entity::ColliderComponent::Reflect() {
        REGISTER_ENUM(ColliderComponent, Type, MeowEngine::entity::ColliderType);
        REGISTER_POINTER(ColliderComponent, Data, entity::ColliderData*, true);
        REGISTER_POINTER(ColliderComponent, Body, physx::PxActor*, false);
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