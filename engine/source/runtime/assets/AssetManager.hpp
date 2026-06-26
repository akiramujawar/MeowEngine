//
// Created by Akira Mujawar on 05/03/26.
//

#ifndef MEOWENGINE_ASSETMANAGER_HPP
#define MEOWENGINE_ASSETMANAGER_HPP

#include "log.hpp"

#include "AssetHandle.hpp"
#include "AssetCache.hpp"
#include "AssetDatabase.hpp"
#include "AssetDirectory.hpp"

#include "Path.hpp"
#include "ShaderAsset.hpp"
#include "World.hpp"

namespace MeowEngine::Asset {
    struct AssetManagerInitData;

    class AssetManager {
    public:
        AssetManager();
        ~AssetManager();

        void Init(const AssetManagerInitData& context);

        void LoadDatabase();
        void SaveDatabase();
        void RebuildDatabase();

        AssetDirectory& GetDirectory() { return Directory; };

        static bool CreateAndSaveEmptyAsset(const AssetHandle& handle, AssetType type,  const Path& path);

        template<typename AssetType>
        AssetHandle CreateTempAsset();

        template<typename AssetType>
        AssetType* GetAsset(const AssetHandle& handle);

        [[nodiscard]] bool HasAssetInDatabase(const AssetHandle& handle) const;

        template<typename AssetType>
        AssetType* LoadAsset(const AssetHandle& handle);

        template<typename AssetType>
        AssetType* GetAssetOrLoad(const AssetHandle& handle);

        template<typename AssetType>
        AssetType* ReloadAsset(const AssetHandle& handle);

        template<typename AssetType>
        void SaveAsset(const AssetHandle& handle);

        template<typename AssetType>
        AssetHandle SaveTempAsset(const AssetHandle& handle, const Path& path);

        void UnloadAsset(const AssetHandle& handle);
        void ClearCache();

    private:
        template<typename AssetType>
        std::unique_ptr<AssetType> LoadAssetInternal(const AssetHandle& handle);

        template<typename AssetType>
        void SaveAssetInternal(const AssetHandle& handle, const Path& path);

        AssetCache Cache;
        AssetDatabase Registry;
        AssetDirectory Directory;
    };

    template <typename AssetType>
    AssetHandle AssetManager::CreateTempAsset() {
        std::unique_ptr<AssetType> asset = std::make_unique<AssetType>();
        auto handle = AssetHandle::CreateTemp();

        Cache.Add(handle, std::move(asset));

        return handle;
    }

    template <typename AssetType>
    AssetType* AssetManager::GetAsset(const AssetHandle& handle) {
        if (Cache.Has(handle)) {
            return &Cache.Get<AssetType>(handle);
        }
        else {
            MeowEngine::Log("Asset", "Not loaded", LogType::ERROR);
            return nullptr;
        }
    }

    template<typename AssetType>
    AssetType* AssetManager::LoadAsset(const AssetHandle& handle) {
        std::unique_ptr<AssetType> asset = LoadAssetInternal<AssetType>(handle);

        if (!asset) {
            return nullptr;
        }

        auto* assetPointer = asset.get();
        Cache.Add(handle, std::move(asset));

        return assetPointer;
    }

    template<typename AssetType>
    AssetType* AssetManager::ReloadAsset(const AssetHandle& handle) {
        std::unique_ptr<AssetType> asset = LoadAssetInternal<AssetType>(handle);

        if (!asset) {
            return nullptr;
        }

        auto* assetPointer = asset.get();
        Cache.Replace(handle, std::move(asset));

        return assetPointer;
    }

    template <typename AssetType>
    void AssetManager::SaveAsset(const AssetHandle& handle) {
        const auto path = Registry.GetAssetPath(handle);
        SaveAssetInternal<AssetType>(handle, path);
    }

    template <typename AssetType>
    AssetHandle AssetManager::SaveTempAsset(const AssetHandle& handle, const Path& path) {
        SaveAssetInternal<AssetType>(handle, path);

        auto newHandle = Registry.Add(path);
        Cache.UpdateKey(newHandle);
        // TODO: update directory

        return newHandle;
    }

    template <typename AssetType>
    AssetType* AssetManager::GetAssetOrLoad(const AssetHandle& handle) {
        if (Cache.Has(handle)) {
            return &Cache.Get<AssetType>(handle);
        }

        if (!Registry.Has(handle)) {
            MeowEngine::Log("Asset", "Not found", LogType::WARNING);
            return nullptr;
        }

        return LoadAsset<AssetType>(handle);
    }

    template<> std::unique_ptr<World> AssetManager::LoadAssetInternal<World>(const AssetHandle& handle);
    template<> std::unique_ptr<ShaderAsset> AssetManager::LoadAssetInternal<ShaderAsset>(const AssetHandle& handle);

    template<> void AssetManager::SaveAssetInternal<World>(const AssetHandle& handle, const Path& path);

}


#endif //MEOWENGINE_ASSETMANAGER_HPP