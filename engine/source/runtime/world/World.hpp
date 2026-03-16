//
// Created by Akira Mujawar on 11/03/26.
//

#ifndef MEOWENGINETEST2_WORLD_HPP
#define MEOWENGINETEST2_WORLD_HPP

#include <entt.hpp>

namespace MeowEngine::Runtime {
    struct  World {
    public:
        World(entt::registry* registry) {
            Registry = registry;
        }
        ~World() {}

        void AddEntity();
        void AddComponent();
        void RemoveComponent();

        entt::registry& GetRegistry() {
            return *Registry;
        }

        [[nodiscard]]
        const entt::registry& GetRegistry() const {
            return *Registry;
        }

    private:
        // TODO: this is temporary until serialization & it's implementation is achieved for dynamic worlds
        entt::registry* Registry;
    };
}

#endif //MEOWENGINETEST2_WORLD_HPP