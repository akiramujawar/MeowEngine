//
// Created by Akira Mujawar on 30/08/24.
//

#include "collider_component.hpp"
#include "reflection_macro_wrapper.hpp"
#include <log.hpp>

using namespace MeowEngine::Runtime;

namespace MeowEngine {
    void Runtime::ColliderComponent::Reflect() {
        REGISTER_POINTER(ColliderComponent, Data, Runtime::ColliderShapeBase*, true, true);
        REGISTER_POINTER(ColliderComponent, Body, physx::PxActor*, false, false);
    }

    ColliderComponent::ColliderComponent(Runtime::BoxColliderShape inData) {
        // TODO: remember to delete the object. currently tracy will be difficult as copy constructor instead of constructor
        // & manually keeping track of these things would be difficult, find a better solution for this
        Data = new BoxColliderShape(std::move(inData));
    }

    ColliderComponent::ColliderComponent(Runtime::SphereColliderShape inData) {
        Data = new SphereColliderShape(std::move(inData));
    }


    Runtime::ColliderShapeBase& ColliderComponent::GetColliderData() {
        return *Data;
    }

    void ColliderComponent::SetPhysicsBody(physx::PxActor *inActor) {
        Body = inActor;
    }
}