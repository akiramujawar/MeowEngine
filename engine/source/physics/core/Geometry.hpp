//
// Created by Akira Mujawar on 04/07/26.
//

#ifndef MEOWENGINE_GEOMETRY_HPP
#define MEOWENGINE_GEOMETRY_HPP

#include <variant>

#include "BoxGeometry.hpp"
#include "SphereGeometry.hpp"
#include "CapsuleGeometry.hpp"

namespace MeowEngine::Physics {
    using Geometry = std::variant<BoxGeometry, SphereGeometry, CapsuleGeometry>;
}

#endif //MEOWENGINE_GEOMETRY_HPP