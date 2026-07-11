//
// Created by Akira Mujawar on 17/06/26.
//

#ifndef MEOWENGINE_RUNTIMEINITDATA_HPP
#define MEOWENGINE_RUNTIMEINITDATA_HPP

#include "PhysicsResultBuffer.hpp"

namespace MeowEngine::Runtime {
    struct RuntimeInitData {
        Physics::PhysicsResultBuffer* PhysicsResultBuffer;
    };
}

#endif //MEOWENGINE_RUNTIMEINITDATA_HPP