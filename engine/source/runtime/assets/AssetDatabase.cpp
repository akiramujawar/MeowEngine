//
// Created by Akira Mujawar on 15/06/26.
//

#include <AssetDatabase.hpp>

#include "Public/Core/Include.hpp"
#include "Public/IO/Include.hpp"

#include "MeowService.hpp"
#include "Project.hpp"

#include "AssetSerializer.hpp"
#include "AssetRegistrySerializer.hpp"

namespace MeowEngine::Asset {
    AssetDatabase::AssetDatabase() {}

    AssetDatabase::~AssetDatabase() {}

    void AssetDatabase::Load() {
        const auto engineAssetRegistryPath = MeowService().Project.Settings.GetEngineAssetResolverPath();
        AssetRegistrySerializer::Deserialize(
            engineAssetRegistryPath, EngineRegistry
        );

        const auto sandboxAssetRegistryPath = MeowService().Project.Settings.GetSandboxAssetResolverPath();
        AssetRegistrySerializer::Deserialize(
            sandboxAssetRegistryPath, SandboxRegistry
        );

        MeowEngine::Log("AssetDatabase", "");
    }

    bool AssetDatabase::Has(const AssetHandle& handle) {
        if (SandboxRegistry.Has(handle)) {
            return true;
        }
        else if (EngineRegistry.Has(handle)) {
            return true;
        }

        return false;
    }

    Path AssetDatabase::GetAssetPath(const AssetHandle& handle) {
        if (SandboxRegistry.Has(handle)) {
            const std::string& path = SandboxRegistry.GetPath(handle);

            return Path {path};
        }
        else if (EngineRegistry.Has(handle)) {
            const std::string& path = EngineRegistry.GetPath(handle);

            return Path {path};
        }

        MeowEngine::Log("AssetDatabase", "GetAssetPath: Cannot find path for handle", LogType::WARNING);
        return Path {""};
    }

    AssetMetadata AssetDatabase::GetAssetMetadata(const AssetHandle& asset) {
        MeowEngine::Log("AssetDatabase", "GetAssetMetadata Not implmented", LogType::ERROR);
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

        return AssetHandle::Null;

        // if (IsEnginePath(path)) {
        //     // get header
        //     // create handle
        //     // create metadata
        //     // store
        // }
    }

    void AssetDatabase::Remove(const AssetHandle& handle) {}

    void AssetDatabase::Rebuild() {
        const auto sandboxAssetsPath = MeowService().Project.Settings.GetExecutablePath() + "assets";
        const auto sandboxAssetRegistryPath = MeowService().Project.Settings.GetSandboxAssetResolverPath();
        UpdateAssetHandles(sandboxAssetsPath, SandboxRegistry);
        AssetRegistrySerializer::Serialize(
            sandboxAssetRegistryPath, SandboxRegistry
        );

        // when running as client we don't run this.
        const auto engineAssetsPath = MeowService().Project.Settings.GetExecutablePath() + "engine/assets";
        const auto engineAssetRegistryPath = MeowService().Project.Settings.GetEngineAssetResolverPath();
        UpdateAssetHandles(engineAssetsPath, EngineRegistry);
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
        const auto engineAssetsPath = MeowService().Project.Settings.GetExecutablePath() + "engine/assets";
        return path.IsLexicallyRelative(engineAssetsPath.GetRawString());
    }

    void AssetDatabase::UpdateAssetHandles(const Path& path, AssetRegistry& assetRegistry) {
        std::unordered_set<AssetHandle> verifiedHandles;

        assetRegistry.Clear();
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
                std::string logMessage = "Start: " + filePath.GetRawString();
                MeowEngine::Log("Asset Serializer", logMessage, LogType::WARNING);

                auto serializer = AssetSerializer::OpenSerializer(filePath, FileSystem::FileMode::READ);
                isValidEngineAsset = AssetSerializer::ReadHeader(serializer, header);

                std::string logMessage2 = "End " + filePath.GetRawString();
                MeowEngine::Log("Asset Serializer", logMessage2, LogType::WARNING);

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
