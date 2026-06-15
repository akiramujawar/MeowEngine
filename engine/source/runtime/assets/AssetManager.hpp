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

namespace MeowEngine::Asset {
    struct AssetManagerInitData;

    class AssetManager {
    public:
        AssetManager();
        ~AssetManager();

        void Init(const AssetManagerInitData& context);
        void Load();

        void RebuidE();

        template<typename Asset>
        Asset& GetAsset(const AssetHandle& handle);

    private:
        void GetMeshAsset();
        void GetBitmapAsset();
        void GetWorldAsset();

    private:
        AssetCache Cache;
        AssetDatabase Registry;
        AssetDirectory Directory;

    };

    template <typename Asset>
    Asset& AssetManager::GetAsset(const AssetHandle& handle) {
        if (Cache.Has(handle)) {
            auto& asset = Cache.GetAsset<Asset>(handle);

            return asset;
        }
        else {
            if (Registry.Has(handle)) {
                return nullptr;
            }
            else {
                MeowEngine::Log("Asset", "Not found", LogType::WARNING);
                return nullptr;
            }
            // Registry.GetAssetPath(handle);
        }
    }
}


#endif //MEOWENGINE_ASSETMANAGER_HPP