//
// Created by Akira Mujawar on 30/08/24.
//

#ifndef MEOWENGINE_COLLIDER_COMPONENT_HPP
#define MEOWENGINE_COLLIDER_COMPONENT_HPP

#include <ComponentBase.hpp>
//#include <collider_type.hpp>

#include <box_collider_shape.hpp>
#include "sphere_collider_shape.hpp"

namespace MeowEngine::Runtime {
    class ColliderComponent : public MeowEngine::Runtime::ComponentBase {

    public:
        REFLECT_COMPONENT(ColliderComponent)
        static void Reflect();

        ColliderComponent() = default;
        ColliderComponent(Runtime::BoxColliderShape inData);
        ColliderComponent(Runtime::SphereColliderShape inData);
        virtual ~ColliderComponent() = default;

        void SetPhysicsBody(physx::PxActor* inActor);

        Runtime::ColliderShapeBase& GetColliderData();

    private:
        // TODO: We need to support, multiple colliders attached as shapes to a rigidbody
        // TODO: Hence we will be refactoring pointer into vector array
        Runtime::ColliderShapeBase* Data;

        // TODO: This is null on render thread. Why was this not null randomly while debugging?
        physx::PxActor* Body;
    };
}


#endif //MEOWENGINE_COLLIDER_COMPONENT_HPP
