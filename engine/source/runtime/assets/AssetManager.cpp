//
// Created by Akira Mujawar on 05/03/26.
//

#include "AssetManager.hpp"

#include "AssetHeader.hpp"
#include "Public/Core/Include.hpp"
#include "log.hpp"
#include "AssetManagerInitData.hpp"
#include "AssetSerializer.hpp"

#include "WorldSerializer.hpp"

namespace MeowEngine::Asset {
    AssetManager::AssetManager() {
        MeowEngine::Log("AssetManager", "Constructed");
    }

    AssetManager::~AssetManager() {
        MeowEngine::Log("AssetManager", "Destructed");
    }

    void AssetManager::Init(const AssetManagerInitData& context) {
        MeowEngine::Log("AssetManager", "Init");
    }

    void AssetManager::LoadDatabase() {
        Registry.Load();
        // Direcotry.Load();
    }

    void AssetManager::SaveDatabase() {}

    void AssetManager::RebuildDatabase() {
        Registry.Rebuild();
        // Directory.RebuildE();
    }

    bool AssetManager::CreateAndSaveEmptyAsset(const AssetHandle& handle, AssetType type,  const Path& path) {
        AssetHeader header {handle.GetUUID(), static_cast<int>(type)};
        header.SettingIndicator = sizeof(Asset::AssetHeader);
        header.SettingSize = 0;
        header.DataIndicator = header.SettingIndicator + header.SettingSize;
        header.DataSize = 0;

        return AssetSerializer::CreateEmptyMeowdata(path, header);
    }

    void AssetManager::UnloadAsset(const AssetHandle& handle) {
        Cache.Remove(handle);
    }

    void AssetManager::ClearCache() {
        Cache.Clear();
    }

    template<>
    std::unique_ptr<World> AssetManager::LoadAssetInternal<World>(const AssetHandle& handle) {
        // actual code
        const auto path = Registry.GetAssetPath(handle);
        auto world = std::make_unique<World>();

        if (!WorldSerializer::Deserialize(path, *world)) {
            MeowEngine::Log("Asset", "Failed loading", LogType::ERROR);
            return nullptr;
        }

        // auto performs move as it's passed by value
        return world;
    }

    template<>
    void AssetManager::SaveAssetInternal<World>(const AssetHandle& handle, const Path& path) {
        auto world = GetAsset<World>(handle);
        if (world != nullptr) {
            if (!WorldSerializer::Serialize(path, *world)) {
                MeowEngine::Log("Asset", "Failed saving", LogType::ERROR);
            }
        }
        else {
            MeowEngine::Log("Asset", "Failed saving", LogType::ERROR);
        }
    }

}
