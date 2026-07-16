//
// Created by Akira Mujawar on 15/06/26.
//

#include <AssetDatabase.hpp>

#include "Public/Core/Include.hpp"
#include "Public/IO/Include.hpp"

#include "MeowService.hpp"
#include "ConfigManager.hpp"

#include "AssetSerializer.hpp"
#include "AssetRegistrySerializer.hpp"

namespace MeowEngine::Asset {
    AssetDatabase::AssetDatabase() {}

    AssetDatabase::~AssetDatabase() {}

    void AssetDatabase::Load() {
        const auto engineAssetRegistryPath = MeowService().ConfigManager.Paths.GetEngineAssetResolverPath();
        AssetRegistrySerializer::Deserialize(
            engineAssetRegistryPath, EngineRegistry
        );

        const auto sandboxAssetRegistryPath = MeowService().ConfigManager.Paths.GetSandboxAssetResolverPath();
        AssetRegistrySerializer::Deserialize(
            sandboxAssetRegistryPath, SandboxRegistry
        );

        MeowEngine::Log("AssetDatabase", "");
    }

    bool AssetDatabase::Has(const AssetHandle& handle) const {
        if (SandboxRegistry.Has(handle)) {
            return true;
        }
        else if (EngineRegistry.Has(handle)) {
            return true;
        }

        return false;
    }

    bool AssetDatabase::Has(const Path& handle) const {
        if (SandboxRegistry.Has(handle)) {
            return true;
        }
        else if (EngineRegistry.Has(handle)) {
            return true;
        }

        return false;
    }

    Path AssetDatabase::GetAssetPath(const AssetHandle& handle) const {
        if (SandboxRegistry.Has(handle)) {
            return SandboxRegistry.GetPath(handle);
        }
        else if (EngineRegistry.Has(handle)) {
            return EngineRegistry.GetPath(handle);
        }

        MeowEngine::Log("AssetDatabase", "GetAssetPath: Cannot find path for handle", LogType::WARNING);
        return Path {""};
    }

    AssetMetadata AssetDatabase::GetAssetMetadata(const AssetHandle& handle) const {
        if (SandboxRegistry.Has(handle)) {
            return SandboxRegistry.GetMetadata(handle);
        }
        else if (EngineRegistry.Has(handle)) {
            return EngineRegistry.GetMetadata(handle);
        }

        return {AssetType::UNKNOWN, "", AssetHandle::Invalid};
    }

    AssetMetadata AssetDatabase::GetAssetMetadata(const Path& path) const {
        if (SandboxRegistry.Has(path)) {
            return SandboxRegistry.GetMetadata(path);
        }
        else if (EngineRegistry.Has(path)) {
            return EngineRegistry.GetMetadata(path);
        }

        return {AssetType::UNKNOWN, "", AssetHandle::Invalid};
    }

    std::vector<AssetMetadata> AssetDatabase::GetEditorAssetHandles() {
        auto map = EngineRegistry.GetMap();
        std::vector<AssetMetadata> assetMetadatas;
        for (auto iter = map.begin(); iter != map.end(); ++iter) {
            assetMetadatas.push_back(iter->second);
        }

        return assetMetadatas;
    }

    AssetHandle AssetDatabase::Add(const Path& path) {
        AssetHeader header;
        bool isValidEngineAsset = false;

        // read file get header & validity of asset (engine asset or not)
        {
            auto serializer = AssetSerializer::OpenSerializer(path, FileSystem::FileMode::READ);
            isValidEngineAsset = AssetSerializer::ReadHeader(serializer, header);

            AssetSerializer::CloseSerializer(serializer);
        }

        if (isValidEngineAsset) {
            AssetHandle handle = AssetHandle::Create(header.UUID);
            AssetMetadata metadata;
            metadata.Type = static_cast<AssetType>(header.Type);
            metadata.Path = path.GetRawString();
            metadata.Handle = handle;

            if (IsEnginePath(path)) {
                EngineRegistry.Add(handle, metadata);
            }
            else {
                SandboxRegistry.Add(handle, metadata);
            }

            return handle;
        }
        else {
            MeowEngine::Log("AssetDatabase", "Invalid path to add");
        }

        return AssetHandle::Invalid;

        // if (IsEnginePath(path)) {
        //     // get header
        //     // create handle
        //     // create metadata
        //     // store
        // }
    }

    void AssetDatabase::Remove(const AssetHandle& handle) {}

    void AssetDatabase::Rebuild() {
        // const auto sandboxAssetsPath = MeowService().Project.Paths.GetExecutablePath() + "assets";
        const auto sandboxAssetRegistryPath = MeowService().ConfigManager.Paths.GetSandboxAssetResolverPath();
        SandboxRegistry.Clear();

        UpdateAssetHandles("assets", SandboxRegistry);
        UpdateAssetHandles("shaders", SandboxRegistry);

        AssetRegistrySerializer::Serialize(
            sandboxAssetRegistryPath, SandboxRegistry
        );

        // when running as client we don't run this.
        // const auto engineAssetsPath = MeowService().Project.Paths.GetExecutablePath() + "engine/assets";
        const auto engineAssetRegistryPath = MeowService().ConfigManager.Paths.GetEngineAssetResolverPath();
        EngineRegistry.Clear();

        UpdateAssetHandles("engine/assets", EngineRegistry);
        UpdateAssetHandles("engine/shaders", EngineRegistry);

        AssetRegistrySerializer::Serialize(
            engineAssetRegistryPath, EngineRegistry
        );
        // for testing --
        // SandboxRegistry.Clear();
        // EngineRegistry.Clear();
        //
        // Load();
    }

    bool AssetDatabase::IsEnginePath(const Path& path) {
        const auto engineAssetsPath = MeowService().ConfigManager.Paths.GetExecutablePath() + "engine/assets";
        return path.IsLexicallyRelative(engineAssetsPath.GetRawString());
    }

    void AssetDatabase::UpdateAssetHandles(const Path& path, AssetRegistry& assetRegistry) {
        std::unordered_set<AssetHandle> verifiedHandles;

        CheckDirectoryForAssetHandles(path, assetRegistry, verifiedHandles);
    }

    void AssetDatabase::CheckDirectoryForAssetHandles(const Path& directoryPath, AssetRegistry& assetRegistry, std::unordered_set<AssetHandle>& verifiedHandles) {
        auto rootDirectory = FileSystem::Directory { directoryPath };

        // for all files inside directory check if newly or updated asset handles
        // - if so add new asset / update existing handle
        auto files = rootDirectory.GetFiles(false);
        for (auto& filePath : files) {
            AssetHeader header;
            bool isValidEngineAsset = false;

            // read file get header & validity of asset (engine asset or not)
            {
                // std::string logMessage = "Start: " + filePath.GetRawString();
                // MeowEngine::Log("Asset Serializer", logMessage, LogType::WARNING);

                auto serializer = AssetSerializer::OpenSerializer(filePath, FileSystem::FileMode::READ);
                isValidEngineAsset = AssetSerializer::ReadHeader(serializer, header);

                // std::string logMessage2 = "End " + filePath.GetRawString();
                // MeowEngine::Log("Asset Serializer", logMessage2, LogType::WARNING);

                AssetSerializer::CloseSerializer(serializer);
            }

            if (isValidEngineAsset) {
                AssetHandle handle = AssetHandle::Create(header.UUID);
                AssetMetadata metadata;
                metadata.Type = static_cast<AssetType>(header.Type);
                metadata.Path = filePath.GetRawString();
                metadata.Handle = handle;

                assetRegistry.Add(handle, metadata);
            }
        }

        // check recursively for each folder in this path
        auto directories = rootDirectory.GetDirectories(false);
        for (auto& path : directories) {
            CheckDirectoryForAssetHandles(path, assetRegistry, verifiedHandles);
        }
    }
}
