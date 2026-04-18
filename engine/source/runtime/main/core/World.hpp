//
// Created by Akira Mujawar on 11/03/26.
//

#ifndef MEOWENGINETEST2_WORLD_HPP
#define MEOWENGINETEST2_WORLD_HPP

#include <entt.hpp>

#include "entt_triple_buffer.hpp"

namespace MeowEngine::Runtime {
    struct  World {
    public:
        World() : Buffer() {}

        ~World() {}

        void AddEntity();
        void AddComponent();
        void RemoveComponent();

        // entt::registry& GetRegistry() {
        //     return *Registry;
        // }
        //
        // [[nodiscard]]
        // const entt::registry& GetRegistry() const {
        //     return *Registry;
        // }

        EnttTripleBuffer& GetBuffer() {
            return Buffer;
        }

    private:
        // TODO: this is temporary until serialization & it's implementation is achieved for dynamic worlds
        // entt::registry* Registry;
        EnttTripleBuffer Buffer;
    };
}

#endif //MEOWENGINETEST2_WORLD_HPP