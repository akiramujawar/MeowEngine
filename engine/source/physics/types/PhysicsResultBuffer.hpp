//
// Created by Akira Mujawar on 11/07/26.
//

#ifndef MEOWENGINE_PHYSICSRESULTBUFFER_HPP
#define MEOWENGINE_PHYSICSRESULTBUFFER_HPP

#include <Public/Threading/Forward.hpp>
#include "PhysicsResult.hpp"

namespace MeowEngine::Physics {
    typedef DoubleBuffer<PhysicsResult> PhysicsResultBuffer;
}
#endif //MEOWENGINE_PHYSICSRESULTBUFFER_HPP