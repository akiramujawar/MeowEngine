//
// Created by Akira Mujawar on 04/07/26.
//

#ifndef MEOWENGINE_PHYSXRIGIDDYNAMIC_HPP
#define MEOWENGINE_PHYSXRIGIDDYNAMIC_HPP

#include <cstdlib>
#include <vector>

#include "PxPhysicsAPI.h"
#include "RigidbodyType.hpp"

namespace MeowEngine::Physics {
    struct PhysXRigidbody {
        uint64_t ObjectID;
        RigidbodyType Type = RigidbodyType::DYNAMIC;

        physx::PxRigidActor* Rigidbody;

        std::vector<uint64_t> ColliderIDs {};
    };
}

#endif //MEOWENGINE_PHYSXRIGIDDYNAMIC_HPP