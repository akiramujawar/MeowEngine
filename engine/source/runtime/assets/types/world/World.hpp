//
// Created by Akira Mujawar on 11/03/26.
//

#ifndef MEOWENGINETEST2_WORLD_HPP
#define MEOWENGINETEST2_WORLD_HPP

#include <unordered_map>

#include "IAsset.hpp"
#include "EntityRegistry.hpp"
#include "EntityHandle.hpp"
#include "EntityComponentChangeData.hpp"


namespace MeowEngine::Asset {
    /**
     * Represents ECS & actions which can be performed on world entities
     */
    class World : public IAsset {
        typedef std::unordered_map<Runtime::EntityID, Runtime::EntityHandle> EntityHandleMap;
        typedef std::vector<EntityComponentChangeData> EntityHandleVector;

        friend class WorldSerializer;
        friend class ComponentSerializer;

    public: // non-static methods
        World();
        ~World() override = default;

        [[nodiscard]] Runtime::EntityRegistry& GetRegistry() { return Registry; }
        [[nodiscard]] const Runtime::EntityRegistry& GetRegistry() const { return Registry; }

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
        void RemoveComponent(const Runtime::EntityHandle& handle);

        template<typename Type>
        Type& GetComponent(Runtime::EntityHandle handle);

        void ClearDirtyEntities();
        [[nodiscard]] const EntityHandleVector& GetDirtyEntities() const { return DirtyEntities; }

    public: // static methods
        template<typename Type>
        static void* GetOrAddComponentToWorld(World& world, const Runtime::EntityHandle& handle);

    public:
        Runtime::EntityHandle ActiveCamera;
        Runtime::EntityHandle SkyBox;
        Runtime::EntityHandle Grid;

    private:
        Runtime::EntityRegistry Registry;
        EntityHandleMap RuntimeEntityMap;
        EntityHandleVector DirtyEntities;
    };

    template <typename Type>
    bool World::HasComponent(const Runtime::EntityHandle& handle) const {
        return Registry.any_of<Type>(handle.GetEntity());
    }

    template <typename Type>
    Type& World::AddComponent(const Runtime::EntityHandle& handle) {
        // track as dirty so systems can specifically process modified entitites
        DirtyEntities.push_back({
            handle,
            EntityComponentChangeType::ADDED,
            Runtime::EntityComponentHash<Type>()
        });

        // add and return
        return Registry.emplace<Type>(handle.GetEntity());
    }

    template <typename Type>
    void World::RemoveComponent(const Runtime::EntityHandle& handle) {

        // track as dirty so systems can specifically process modified entitites
        DirtyEntities.push_back({
            handle,
            EntityComponentChangeType::REMOVED,
            Runtime::EntityComponentHash<Type>()
        });

        // remove
        Registry.erase<Type>(handle.GetEntity());
    }

    template <typename Type>
    Type& World::GetComponent(Runtime::EntityHandle handle) {
        return Registry.get<Type>(handle.GetEntity());
    }

    template <typename Type>
    void* World::GetOrAddComponentToWorld(World& world, const Runtime::EntityHandle& handle) {
        if (world.HasComponent<Type>(handle)) {
            return &world.GetComponent<Type>(handle);
        }

        return &world.AddComponent<Type>(handle);
    }
}

#endif //MEOWENGINETEST2_WORLD_HPP