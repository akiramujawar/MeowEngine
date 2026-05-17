//
// Created by Akira Mujawar on 18/04/26.
//

#ifndef MEOWENGINE_PHYSICSCOMMAND_HPP
#define MEOWENGINE_PHYSICSCOMMAND_HPP

#include <vector>
#include <Rigidbody.hpp>

namespace MeowEngine::Physics {
    struct PhysicsCommand {
        std::vector<int32_t> Added;
        std::vector<int32_t> Removed;
        std::vector<Rigidbody> Updated;
    };
}

#endif //MEOWENGINE_PHYSICSCOMMAND_HPP