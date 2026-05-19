//
// Created by Akira Mujawar on 11/03/26.
//

#ifndef MEOWENGINETEST2_WORLD_HPP
#define MEOWENGINETEST2_WORLD_HPP

#include <entt.hpp>

#include "entt_triple_buffer.hpp"

namespace MeowEngine::Runtime {
    /**
     * Represents ECS & actions which can be performed on world entities
     */
    struct World {
    public:
        World() : Buffer() {}

        ~World() {}

        entt::entity AddEntity();
        void RemoveEntity(entt::entity entity);

        template<typename Type>
        Type& AddComponent(const entt::entity& entity);

        template<typename Type>
        void RemoveComponent(entt::entity entity);

        template<typename Type>
        void GetComponent(entt::entity entity);

        entt::registry& GetRegistry() {
            return Registry;
        }

        [[nodiscard]]
        const entt::registry& GetRegistry() const {
            return Registry;
        }

        EnttTripleBuffer& GetBuffer() {
            return Buffer;
        }

    public:
        entt::entity ActiveCamera;
        entt::entity SkyBox;

    private:
        entt::registry Registry;

        // TODO: this is temporary until serialization & it's implementation is achieved for dynamic worlds
        EnttTripleBuffer Buffer;
    };

    template <typename Type>
    Type& MeowEngine::Runtime::World::AddComponent(const entt::entity& entity) {
        return Registry.emplace<Type>(entity);
    }
}

#endif //MEOWENGINETEST2_WORLD_HPP