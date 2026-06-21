//
// Created by Akira Mujawar on 19/06/26.
//

#ifndef MEOWENGINE_ENTITYID_HPP
#define MEOWENGINE_ENTITYID_HPP

#include <cstdint>

namespace MeowEngine::Runtime {
    /**
     * Used to represent guid of entity for serialization
     */
    enum class EntityID : std::uint64_t {
        INVALID = 0
    };
}

#endif //MEOWENGINE_ENTITYID_HPP