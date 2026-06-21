//
// Created by Akira Mujawar on 11/03/26.
//

#ifndef MEOWENGINETEST2_WORLD_HPP
#define MEOWENGINETEST2_WORLD_HPP


#include "IAsset.hpp"
#include "EntityRegistry.hpp"
#include "EntityHandle.hpp"

// #include "entt_triple_buffer.hpp"

namespace MeowEngine::Asset {
    /**
     * Represents ECS & actions which can be performed on world entities
     */
    class World : public IAsset {
    public:
        World();
        ~World() override = default;

        /**
         * Empty entity (no components)
         * @return
         */
        Runtime::EntityHandle AddEntity();
        Runtime::EntityHandle AddEntity(Runtime::EntityID guid);
        Runtime::EntityHandle FindHandle(Runtime::EntityID guid);

        void RemoveEntity(Runtime::EntityID guid);
        bool Has(const Runtime::EntityHandle& handle);

        template<typename Type>
        Type& AddComponent(const Runtime::EntityHandle& entity);

        template<typename Type>
        void RemoveComponent(Runtime::EntityHandle entity);

        template<typename Type>
        Type& GetComponent(Runtime::EntityHandle entity);

        [[nodiscard]] Runtime::EntityRegistry& GetRegistry() { return Registry; }
        [[nodiscard]] const Runtime::EntityRegistry& GetRegistry() const { return Registry; }
        // EnttTripleBuffer& GetBuffer() { return Buffer; }

    public:
        Runtime::EntityHandle ActiveCamera;
        Runtime::EntityHandle SkyBox;

    private:
        Runtime::EntityRegistry Registry;

        // TODO: this is temporary until serialization & it's implementation is achieved for dynamic worlds
        // EnttTripleBuffer Buffer;
    };

    template <typename Type>
    Type& World::AddComponent(const Runtime::EntityHandle& handle) {
        return Registry.emplace<Type>(handle.GetEntity());
    }

    template <typename Type>
    Type& World::GetComponent(Runtime::EntityHandle handle) {
        return Registry.get<Type>(handle.GetEntity());
    }
}

#endif //MEOWENGINETEST2_WORLD_HPP