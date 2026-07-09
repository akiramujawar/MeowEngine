//
// Created by Akira Mujawar on 06/07/26.
//

#ifndef MEOWENGINE_PHYSICSWORLDDATA_HPP
#define MEOWENGINE_PHYSICSWORLDDATA_HPP

#include <vector>

#include "Rigidbody.hpp"
#include "Collider.hpp"
#include "PhysicsMaterial.hpp"

namespace MeowEngine::Physics {
    struct PhysicsWorldData {
        std::vector<Rigidbody> Rigidbodies;
        std::vector<Collider> Colliders;
        std::vector<PhysicsMaterial> Materials;
    };
}

#endif //MEOWENGINE_PHYSICSWORLDDATA_HPP