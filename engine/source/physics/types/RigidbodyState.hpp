//
// Created by Akira Mujawar on 11/07/26.
//

#ifndef MEOWENGINE_RIGIDBODYSTATE_HPP
#define MEOWENGINE_RIGIDBODYSTATE_HPP

#include <cstdlib>

#include "Public/Math.hpp"

namespace MeowEngine::Physics {

    struct RigidbodyState {
        uint64_t ObjectID;

        Vector3 Position;
        Quaternion Quaternion;
    };

}

#endif //MEOWENGINE_RIGIDBODYSTATE_HPP