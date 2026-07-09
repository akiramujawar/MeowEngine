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
#include "ShaderSerialization.hpp"
#include "TextureSerializer.hpp"
#include "MeshSerializer.hpp"
#include "PhysicsMaterialSerializer.hpp"

// runtime only assets
#include "TransformGizmoAsset.hpp"

namespace MeowEngine::Asset {
    AssetManager::AssetManager() {
        MeowEngine::Log("AssetManager", "Constructed");
    }

    AssetManager::~AssetManager() {
        MeowEngine::Log("AssetManager", "Destructed");
    }

    void AssetManager::Init(const AssetManagerInitData& context) {
        MeowEngine::Log("AssetManager", "Init");

        Directory.Init();
    }

    void AssetManager::LoadAndBuild() {
        Registry.Load();
        Directory.LoadAndBuild();

        // load editor assets here
        const auto editorMetadatas = Registry.GetEditorAssetHandles();
        for (auto& metadata : editorMetadatas) {
            switch (metadata.Type) {
                case AssetType::SHADER:
                    break;
                case AssetType::TEXTURE:
                    LoadAsset<BitmapAsset>(metadata.Handle);
                    break;
                case AssetType::MESH:
                    break;
                case AssetType::WORLD:
                    break;
                case AssetType::MATERIAL:
                    break;
                default:
                    break;
            }
        }

        // create session assets
        Session.TransformGizmoHandle = CreateTempAsset<TransformGizmoAsset>();
    }

    void AssetManager::SaveDatabase() {}

    void AssetManager::RebuildDatabase() {
        Registry.Rebuild();
        Directory.Rebuild();
    }

    bool AssetManager::CreateAndSaveEmptyAsset(const AssetHandle& handle, AssetType type,  const Path& path) {
        AssetHeader header {handle.GetUUID(), static_cast<int>(type)};
        header.SettingIndicator = sizeof(Asset::AssetHeader);
        header.SettingSize = 0;
        header.DataIndicator = header.SettingIndicator + header.SettingSize;
        header.DataSize = 0;

        return AssetSerializer::CreateEmptyMeowdata(path, header);
    }

    bool AssetManager::HasAssetInDatabase(const AssetHandle& handle) const {
        return Registry.Has(handle);
    }

    void AssetManager::UnloadAsset(const AssetHandle& handle) {
        Cache.Remove(handle);
    }

    void AssetManager::ClearCache() {
        Cache.Clear();
    }

    bool AssetManager::IsLoaded(const AssetHandle& handle) const {
        return Cache.Has(handle);
    }

    template<>
    std::unique_ptr<World> AssetManager::LoadAssetInternal<World>(const AssetHandle& handle) {
        // actual code
        const auto& path = Registry.GetAssetPath(handle);
        auto world = std::make_unique<World>();

        if (!WorldSerializer::Deserialize(path, *world)) {
            MeowEngine::Log("World Asset", "Failed loading", LogType::ERROR);
            return nullptr;
        }

        // auto performs move as it's passed by value
        return world;
    }

    template<>
    std::unique_ptr<ShaderAsset> AssetManager::LoadAssetInternal<ShaderAsset>(const AssetHandle& handle) {
        // actual code
        const auto& path = Registry.GetAssetPath(handle);
        auto asset = std::make_unique<ShaderAsset>();

        if (!ShaderSerialization::Deserialize(path, *asset)) {
            MeowEngine::Log("Shader Asset", "Failed loading", LogType::ERROR);
            return nullptr;
        }

        // auto performs move as it's passed by value
        return asset;
    }

    template<>
    std::unique_ptr<BitmapAsset> AssetManager::LoadAssetInternal<BitmapAsset>(const AssetHandle& handle) {
        // actual code
        const auto& path = Registry.GetAssetPath(handle);
        auto asset = std::make_unique<BitmapAsset>();

        if (!TextureSerializer::Deserialize(path, *asset)) {
            MeowEngine::Log("Shader Asset", "Failed loading", LogType::ERROR);
            return nullptr;
        }

        // auto performs move as it's passed by value
        return asset;
    }

    template<>
    std::unique_ptr<MeshAsset> AssetManager::LoadAssetInternal<MeshAsset>(const AssetHandle& handle) {
        // actual code
        const auto& path = Registry.GetAssetPath(handle);
        auto asset = std::make_unique<MeshAsset>();

        if (!MeshSerializer::Deserialize(path, *asset)) {
            MeowEngine::Log("Shader Asset", "Failed loading", LogType::ERROR);
            return nullptr;
        }

        // auto performs move as it's passed by value
        return asset;
    }

    template <>
    std::unique_ptr<PhysicsMaterialAsset> AssetManager::LoadAssetInternal<PhysicsMaterialAsset>(const AssetHandle& handle) {
        // actual code
        const auto& path = Registry.GetAssetPath(handle);
        auto asset = std::make_unique<PhysicsMaterialAsset>();

        if (!PhysicsMaterialSerializer::Deserialize(path, *asset)) {
            MeowEngine::Log("Physics Material Asset", "Failed loading", LogType::ERROR);
            return nullptr;
        }

        // auto performs move as it's passed by value
        return asset;
    }

    template<>
    void AssetManager::SaveAssetInternal<World>(const AssetHandle& handle, const Path& path) {
        auto world = GetAsset<World>(handle);
        if (world != nullptr) {
            if (!WorldSerializer::Serialize(path, *world)) {
                MeowEngine::Log("World Asset", "Failed saving", LogType::ERROR);
            }
        }
        else {
            MeowEngine::Log("Asset", "Failed saving", LogType::ERROR);
        }
    }

    template <>
    void AssetManager::SaveAssetInternal<PhysicsMaterialAsset>(const AssetHandle& handle, const Path& path) {
        auto asset = GetAsset<PhysicsMaterialAsset>(handle);
        if (asset != nullptr) {
            if (!PhysicsMaterialSerializer::Serialize(path, *asset)) {
                MeowEngine::Log("Physics Material Asset", "Failed saving", LogType::ERROR);
            }
        }
        else {
            MeowEngine::Log("Asset", "Failed saving", LogType::ERROR);
        }
    }
}
