//
// Created by Akira Mujawar on 04/07/26.
//

#ifndef MEOWENGINE_PHYSXMATERIAL_HPP
#define MEOWENGINE_PHYSXMATERIAL_HPP

#include <cstdlib>
#include "PxPhysicsAPI.h"

namespace MeowEngine::Physics {
    struct PhysXMaterial {
        uint64_t GUID;

        physx::PxMaterial* Material;
    };
}

#endif //MEOWENGINE_PHYSXMATERIAL_HPP