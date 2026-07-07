//
// Created by Akira Mujawar on 04/07/26.
//

#ifndef MEOWENGINE_GEOMETRY_HPP
#define MEOWENGINE_GEOMETRY_HPP

#include <variant>

#include "ColliderType.hpp"

#include "PlaneGeometry.hpp"
#include "BoxGeometry.hpp"
#include "SphereGeometry.hpp"
#include "CapsuleGeometry.hpp"
#include "MeshGeometry.hpp"

namespace MeowEngine::Physics {
    struct Geometry {
        union {
            PlaneGeometry Plane;
            BoxGeometry Box;
            SphereGeometry Sphere;
            CapsuleGeometry Capsule;
            MeshGeometry Mesh;
        };
    };

}

#endif //MEOWENGINE_GEOMETRY_HPP