//
// Created by Akira Mujawar on 04/07/26.
//

#ifndef MEOWENGINE_PHYSXCOLLIDER_HPP
#define MEOWENGINE_PHYSXCOLLIDER_HPP

#include <cstdlib>

#include "PxPhysicsAPI.h"
#include "ColliderType.hpp"

namespace MeowEngine::Physics {
    // phsx
    struct PhysXCollider {
        uint64_t GUID;
        ColliderType Type;
        physx::PxShape* Collider;
    };

}

#endif //MEOWENGINE_PHYSXCOLLIDER_HPP