//
// Created by Akira Mujawar on 11/03/26.
//

#ifndef MEOWENGINETEST2_WORLD_HPP
#define MEOWENGINETEST2_WORLD_HPP

#include <entt.hpp>

namespace MeowEngine::Runtime {
    class World {
    public:
        void AddEntity();
        void AddComponent();
        void RemoveComponent();

        entt::registry& GetRegistry() {
            return Registry;
        }

    private:
        entt::registry Registry;
    };
}


#endif //MEOWENGINETEST2_WORLD_HPP