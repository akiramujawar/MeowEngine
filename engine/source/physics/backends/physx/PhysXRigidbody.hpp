//
// Created by Akira Mujawar on 04/07/26.
//

#ifndef MEOWENGINE_PHYSXACTOR_HPP
#define MEOWENGINE_PHYSXACTOR_HPP

#include <cstdlib>
#include "PxPhysicsAPI.h"

namespace MeowEngine::Physics {
    struct PhysXRigidbody {
        uint64_t ObjectID;

        physx::PxActor* Rigidbody;
    };
}

#endif //MEOWENGINE_PHYSXACTOR_HPP