//
// Created by Akira Mujawar on 24/06/26.
//

#include "FileCache.hpp"

#include "Public/Core/Include.hpp"
#include "Public/IO/Include.hpp"

#include "AssetDatabase.hpp"

namespace MeowEngine::Asset {
    bool FileCache::HasFile(const Path& path) {
        const auto iterator = Files.find(path);
        return iterator != Files.end();
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    bool FileCache::IsValidFolder(const Path& path) {
        return FileSystem::FileSystem::IsDirectory(path);
    }

    std::vector<DirectoryAsset> FileCache::Get(const Path& path) {
        const auto iterator = Files.find(path);
        return iterator->second;
    }

    std::vector<DirectoryAsset> FileCache::LoadAndGet(const Path& path, const AssetDatabase& database) {
        FileSystem::Directory directory(path);
        auto subPaths = directory.GetAll(false);
        std::vector<DirectoryAsset> result;

        for (const auto& subPath : subPaths) {
            // for folder we create dummy directory asset
            if (IsValidFolder(subPath)) {
                DirectoryAsset asset {
                    true,
                    subPath,
                    subPath.GetName().GetString(),
                    AssetType::FOLDER,
                    AssetHandle::Null,
                    AssetHandle::Null,
                };

                result.push_back(asset);
            }
            // for asset from database we retrieve the essential data
            else if (database.Has(subPath)) {
                auto metadata = database.GetAssetMetadata(subPath);
                DirectoryAsset asset {
                    false,
                    subPath,
                    subPath.GetName().GetString(),
                    metadata.Type,
                    AssetHandle::Null,
                    metadata.Handle,
                };

                result.push_back(asset);
            }
        }

        Files.try_emplace(path, result);
        return result;
    }

}
