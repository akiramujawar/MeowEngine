//
// Created by Akira Mujawar on 15/05/26.
//

#ifndef MEOWENGINE_WORLDMANAGER_HPP
#define MEOWENGINE_WORLDMANAGER_HPP

#include <unordered_map>
#include <functional>

#include <AssetHandle.hpp>


namespace MeowEngine::Runtime {
    class GameplaySystem;
    class World;

    /**
     * Manages the sync/async saving/loading/unloading of world & it's resources
     */
    class WorldManager {
        friend class RuntimeModule;

        WorldManager();
        ~WorldManager();

        static void Init(WorldManager* manager, GameplaySystem* gameplay);

    public:
        /**
         * Loads the world from disk into memory
         * @return
         */
        static void Load(const Asset::AssetHandle& world);
        void LoadAsync(const Asset::AssetHandle& world, std::function<void()> callback);

        /**
         * Unloads the world from memory
         */
        void Unload(const Asset::AssetHandle& world);
        void UnloadAsync(const Asset::AssetHandle& world, std::function<void()> callback);

        /**
         * Reloads world
         * (always faster than Load(), since the dependent assets are already in memory)
         */
        void Reload(const Asset::AssetHandle& world);
        void ReloadAsync(const Asset::AssetHandle& world, std::function<void()> callback);

        /**
         * Switches the active scene
         */
        void Switch(const Asset::AssetHandle& world);

        /**
         * Loads the world and adds entities to world
         * @param world loads the world if not in memory
         */
        void Add(const Asset::AssetHandle& world);

        /**
         * Saves the world on to disk
         * @param world
         */
        void Save(const Asset::AssetHandle& world);

    private:
        static WorldManager* Instance;
        GameplaySystem* Gameplay;

        Asset::AssetHandle ActiveWorld;
        std::unordered_map<Asset::AssetHandle, World*> Worlds;
    };

}


#endif //MEOWENGINE_WORLDMANAGER_HPP