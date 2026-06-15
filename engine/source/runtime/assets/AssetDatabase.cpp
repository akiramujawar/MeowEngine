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
        const auto sandboxAssetRegistryPath = MeowService().Project.Settings.GetSandboxAssetResolverPath();

        AssetRegistrySerializer::Deserialize(
            engineAssetRegistryPath, EngineRegistry
        );

        AssetRegistrySerializer::Deserialize(
            sandboxAssetRegistryPath, SandboxRegistry
        );
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
        const std::string& path = EngineRegistry.GetPath(handle);

        return Path {path};
    }

    AssetMetadata AssetDatabase::GetAssetMetadata(const AssetHandle& asset) {}

    void AssetDatabase::Add(const AssetHandle& handle) {
        // EngineRegistry.Add()
    }

    void AssetDatabase::Remove(const AssetHandle& handle) {}

    void AssetDatabase::RebuildE() {
        // read all files & access there guid - access filesystem to read file
        // - check if guid exists in registry
        //      - if exists
        //          - check if path is correct
        //              - if path not correct update it
        // - if not exists
        //      - add to registry
        // - add to verified
        // - compare verified vs asset registry
        //      - if items missing from verified
        //          - remove them from asset registry

        std::unordered_set<AssetHandle> verifiedHandles;
        auto rootPath = MeowService().Project.Settings.GetExecutablePath() + "assets";
        auto rootDirectory = FileSystem::Directory { rootPath };
        auto directories = rootDirectory.GetDirectories(false);
        auto files = rootDirectory.GetFiles(false);

        for (auto& filePath : files) {
            AssetHeader header;

            // if false, we assume it's not engine readable
            if (AssetSerializer::Deserialize(filePath, header)) {
                // temporary handle for checking assets
                auto handle = AssetHandle::Create(header.UUID);

                if (SandboxRegistry.Has(handle)) {
                    if (SandboxRegistry.GetPath(handle) == filePath.GetStringView()) {
                        // all good
                    }
                    else {
                        auto metadata = SandboxRegistry.GetMetadata(handle);
                        SandboxRegistry.Remove(handle);
                        metadata.Path = filePath.GetRawString();

                        SandboxRegistry.Add(handle, metadata);
                    }
                }
                else {
                    AssetMetadata metadata;
                    metadata.Path = filePath.GetRawString();
                    metadata.Type = static_cast<AssetType>(header.Type);
                    metadata.Handle = handle;

                    SandboxRegistry.Add(handle, metadata);
                }

                verifiedHandles.insert(handle);
            }
        }

        // TODO: do the same and loop for directory inside

        for (auto& verifiedHandle : verifiedHandles) {
            MeowEngine::Log("AssetDatabase", std::to_string(verifiedHandle.GetUUID()));
        }
    }
}
