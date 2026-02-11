//
// Created by Akira Mujawar on 30/08/24.
//

#include "collider_component.hpp"
#include "reflection_macro_wrapper.hpp"
#include <log.hpp>

using namespace MeowEngine::entity;

namespace MeowEngine {
    void entity::ColliderComponent::Reflect() {
        REGISTER_POINTER(ColliderComponent, Data, entity::ColliderData*, true, true);
        REGISTER_POINTER(ColliderComponent, Body, physx::PxActor*, false, false);
    }

    ColliderComponent::ColliderComponent(entity::BoxColliderData inData) {
        // TODO: remember to delete the object. currently tracy will be difficult as copy constructor instead of constructor
        // & manually keeping track of these things would be difficult, find a better solution for this
        Data = new BoxColliderData(std::move(inData));
    }

    ColliderComponent::ColliderComponent(entity::SphereColliderData inData) {
        Data = new SphereColliderData(std::move(inData));
    }


    entity::ColliderData& ColliderComponent::GetColliderData() {
        return *Data;
    }

    void ColliderComponent::SetPhysicsBody(physx::PxActor *inActor) {
        Body = inActor;
    }
}