//
// Created by Akira Mujawar on 07/07/26.
//

#ifndef MEOWENGINE_MATERIAL_HPP
#define MEOWENGINE_MATERIAL_HPP

#include "cstdlib"

namespace MeowEngine::Physics {
    struct PhysicsMaterial {
        uint64_t ObjectID;

        float StaticFriction;
        float DynamicFriction;
        float Restitution;
    };
}

#endif //MEOWENGINE_MATERIAL_HPP