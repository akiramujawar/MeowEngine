//
// Created by Akira Mujawar on 04/07/26.
//

#ifndef MEOWENGINE_RIGIDBODY_HPP
#define MEOWENGINE_RIGIDBODY_HPP

#include <cstdlib>
#include <vector>

#include "RigidbodyType.hpp"

namespace MeowEngine::Physics {
    struct Rigidbody {
        uint64_t ObjectID {};
        RigidbodyType Type = RigidbodyType::DYNAMIC;

        std::vector<uint64_t> ColliderIDs {};
    };
}

#endif //MEOWENGINE_RIGIDBODY_HPP