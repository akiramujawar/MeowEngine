//
// Created by Akira Mujawar on 04/07/26.
//

#ifndef MEOWENGINE_COLLIDER_HPP
#define MEOWENGINE_COLLIDER_HPP

#include <cstdlib>

#include "Geometry.hpp"
#include "ColliderType.hpp"

namespace MeowEngine::Physics {
    struct Collider {
        uint64_t GUID;
        ColliderType Type;
        Geometry Geometry;
    };
}

#endif //MEOWENGINE_COLLIDER_HPP