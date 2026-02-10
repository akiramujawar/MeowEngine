//
// Created by Akira Mujawar on 01/09/24.
//

#ifndef MEOWENGINE_COLLIDER_DATA_HPP
#define MEOWENGINE_COLLIDER_DATA_HPP

#include "m_object.hpp"
#include "PxPhysicsAPI.h"

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

        virtual physx::PxGeometry& GetGeometry() = 0;
    };
}


#endif //MEOWENGINE_COLLIDER_DATA_HPP
