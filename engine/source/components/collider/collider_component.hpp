//
// Created by Akira Mujawar on 30/08/24.
//

#ifndef MEOWENGINE_COLLIDER_COMPONENT_HPP
#define MEOWENGINE_COLLIDER_COMPONENT_HPP

#include <component_base.hpp>
//#include <collider_type.hpp>

#include <box_collider_data.hpp>
#include "sphere_collider_data.hpp"

namespace MeowEngine::entity {
    class ColliderComponent : public MeowEngine::entity::ComponentBase {

    public:
        REFLECT_COMPONENT(ColliderComponent)
        static void Reflect();

        ColliderComponent(entity::BoxColliderData inData);
        ColliderComponent(entity::SphereColliderData inData);
        virtual ~ColliderComponent() = default;

        void SetPhysicsBody(physx::PxActor* inActor);

        entity::ColliderData& GetColliderData();

    private:
        // TODO: We need to support, multiple colliders attached as shapes to a rigidbody
        // TODO: Hence we will be refactoring pointer into vector array
        entity::ColliderData* Data;

        // TODO: This is null on render thread. Why was this not null randomly while debugging?
        physx::PxActor* Body;
    };
}


#endif //MEOWENGINE_COLLIDER_COMPONENT_HPP
