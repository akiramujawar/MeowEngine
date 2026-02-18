//
// Created by Akira Mujawar on 01/09/24.
//

#ifndef MEOWENGINE_COLLIDER_DATA_HPP
#define MEOWENGINE_COLLIDER_DATA_HPP

#include "PxPhysicsAPI.h"

#include "m_object.hpp"
#include <collider_type.hpp>

namespace MeowEngine::entity {
    /**
     * This class is cached as pointer and extended by child classes
     * for clear definitions like a box, sphere, mesh colliders
     * This helps to have a single component with support for different styles of colliders.
     * TODO: Check if this restricts from having multiple colliders on same entity
     */
    class ColliderData : MObject {
    public:
        REFLECT_MObject(ColliderData)
        static void Reflect() {}

        template<typename Type>
        Type& Cast() {
            return *dynamic_cast<Type*>(this);
        }

        entity::ColliderType& GetType() { return Type; };

        virtual physx::PxGeometry& GetGeometry() = 0;
        virtual physx::PxMaterial& GetMaterial() = 0;
        virtual physx::PxShape& GetShape() = 0;

        virtual void CreateGeometry() = 0; // pass transform scale
        virtual void CreateMaterial(physx::PxPhysics*) = 0;
        virtual void CreateShape(physx::PxPhysics*) = 0;

    protected:
        MeowEngine::entity::ColliderType Type;
    };
}


#endif //MEOWENGINE_COLLIDER_DATA_HPP
