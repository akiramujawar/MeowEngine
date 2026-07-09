//
// Created by Akira Mujawar on 04/07/26.
//

#ifndef MEOWENGINE_RIGIDBODY_HPP
#define MEOWENGINE_RIGIDBODY_HPP

#include <cstdlib>

namespace MeowEngine::Physics {
    struct Rigidbody {
        uint64_t ObjectID;

        std::vector<uint64_t> ColliderIDs;
    };
}

#endif //MEOWENGINE_RIGIDBODY_HPP