//
// Created by Akira Mujawar on 21/06/26.
//

#ifndef MEOWENGINE_ENTITY_HPP
#define MEOWENGINE_ENTITY_HPP

#include "cstdint"

namespace MeowEngine::Runtime {
    /**
     * Used to represent entt::entity inside entt registry
     */
    enum class Entity : std::uint32_t {
        INVALID = 0,
    };
}

#endif //MEOWENGINE_ENTITY_HPP