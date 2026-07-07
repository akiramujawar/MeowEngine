//
// Created by Akira Mujawar on 05/07/26.
//

#ifndef MEOWENGINE_RIGIDBODYTYPE_HPP
#define MEOWENGINE_RIGIDBODYTYPE_HPP

#include "reflection_macro_wrapper.hpp"

namespace MeowEngine::Physics {
    enum class RigidbodyType : int{
        STATIC,
        DYNAMIC,
        KINEMATIC
    }; REFLECT_ENUM(Physics, RigidbodyType)
}

#endif //MEOWENGINE_RIGIDBODYTYPE_HPP