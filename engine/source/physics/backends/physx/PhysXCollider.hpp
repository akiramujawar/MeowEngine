//
// Created by Akira Mujawar on 04/07/26.
//

#ifndef MEOWENGINE_PHYSXCOLLIDER_HPP
#define MEOWENGINE_PHYSXCOLLIDER_HPP

#include <cstdlib>

#include "PxPhysicsAPI.h"
#include "ColliderType.hpp"
#include "PhysXMaterial.hpp"

namespace MeowEngine::Physics {
    // phsx
    struct PhysXCollider {
        uint64_t ObjectID;

        ColliderType Type;
        physx::PxShape* Collider;

        uint64_t MaterialID;
    };

}

#endif //MEOWENGINE_PHYSXCOLLIDER_HPP