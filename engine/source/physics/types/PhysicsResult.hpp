//
// Created by Akira Mujawar on 18/04/26.
//

#ifndef MEOWENGINE_PHYSICSRESULT_HPP
#define MEOWENGINE_PHYSICSRESULT_HPP

#include "RigidbodyState.hpp"

namespace MeowEngine::Physics {
    struct PhysicsResult {
        std::vector<RigidbodyState> RigidBodies {};
    };
}

#endif //MEOWENGINE_PHYSICSRESULT_HPP