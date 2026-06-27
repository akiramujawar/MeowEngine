//
// Created by Akira Mujawar on 11/03/26.
//

#ifndef MEOWENGINETEST2_WORLD_HPP
#define MEOWENGINETEST2_WORLD_HPP

#include <unordered_map>

#include "IAsset.hpp"
#include "EntityRegistry.hpp"
#include "EntityHandle.hpp"


namespace MeowEngine::Asset {
    /**
     * Represents ECS & actions which can be performed on world entities
     */
    class World : public IAsset {
        friend class WorldSerializer;
        friend class ComponentSerializer;

    public:
        World();
        ~World() override = default;

        /**
         * Empty entity (no components)
         * @return
         */
        Runtime::EntityHandle AddEntity();
        Runtime::EntityHandle AddEntity(Runtime::EntityID guid);
        Runtime::EntityHandle GetHandle(Runtime::EntityID guid);

        void RemoveEntity(Runtime::EntityID guid);
        bool HasEntity(const Runtime::EntityHandle& handle);
        template <typename Type>
        [[nodiscard]] bool HasComponent(const Runtime::EntityHandle& handle) const;

        template<typename Type>
        Type& AddComponent(const Runtime::EntityHandle& handle);

        template<typename Type>
        static void* AddComponentToWorld(World& world, const Runtime::EntityHandle& handle);

        template<typename Type>
        void RemoveComponent(Runtime::EntityHandle handle);

        template<typename Type>
        Type& GetComponent(Runtime::EntityHandle handle);

        [[nodiscard]] Runtime::EntityRegistry& GetRegistry() { return Registry; }
        [[nodiscard]] const Runtime::EntityRegistry& GetRegistry() const { return Registry; }

    public:
        Runtime::EntityHandle ActiveCamera;
        Runtime::EntityHandle SkyBox;

    private:
        Runtime::EntityRegistry Registry;
        std::unordered_map<Runtime::EntityID, Runtime::EntityHandle> RuntimeEntityMap;
    };

    template <typename Type>
    bool World::HasComponent(const Runtime::EntityHandle& handle) const {
        return Registry.any_of<Type>(handle.GetEntity());
    }

    template <typename Type>
    Type& World::AddComponent(const Runtime::EntityHandle& handle) {
        return Registry.emplace<Type>(handle.GetEntity());
    }

    template <typename Type>
    void* World::AddComponentToWorld(World& world, const Runtime::EntityHandle& handle) {
        if (world.HasComponent<Type>(handle)) {
            return &world.GetComponent<Type>(handle);
        }

        return &world.AddComponent<Type>(handle);
    }

    template <typename Type>
    Type& World::GetComponent(Runtime::EntityHandle handle) {
        return Registry.get<Type>(handle.GetEntity());
    }
}

#endif //MEOWENGINETEST2_WORLD_HPP