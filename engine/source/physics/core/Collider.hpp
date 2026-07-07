//
// Created by Akira Mujawar on 04/07/26.
//

#ifndef MEOWENGINE_COLLIDER_HPP
#define MEOWENGINE_COLLIDER_HPP

#include <cstdlib>

#include "Geometry.hpp"

namespace MeowEngine::Physics {
    struct Collider {
        uint64_t RootObjectID; // do we even need this?
        uint64_t ObjectID;
        ColliderType Type;
        Geometry Geometry;
    };
}

#endif //MEOWENGINE_COLLIDER_HPP