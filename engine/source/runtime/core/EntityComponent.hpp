//
// Created by Akira Mujawar on 19/06/26.
//

#ifndef MEOWENGINE_COMPONENTID_HPP
#define MEOWENGINE_COMPONENTID_HPP

#include "cstdlib"
#include "entt.hpp"

namespace MeowEngine::Runtime {
    /**
     * Handled internally via entt registry
     * NOTE: not to be used outside EnTT registry
     */
    using EntityComponent = std::uint32_t;

    template <typename Type>
    constexpr EntityComponent EntityComponentHash() noexcept {
        return entt::type_hash<Type>::value();
    }
}

#endif //MEOWENGINE_COMPONENTID_HPP