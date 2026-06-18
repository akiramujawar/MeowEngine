//
// Created by Akira Mujawar on 17/06/26.
//

#ifndef MEOWENGINE_THREADTYPE_HPP
#define MEOWENGINE_THREADTYPE_HPP

#include <cstdint>

namespace MeowEngine::Messaging {
    enum class ThreadType : uint8_t {
        NONE,
        MAIN,
        RENDER,
        PHYSICS
    };
}

#endif //MEOWENGINE_THREADTYPE_HPP