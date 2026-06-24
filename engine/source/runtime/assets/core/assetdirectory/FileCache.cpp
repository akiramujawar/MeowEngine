//
// Created by Akira Mujawar on 24/06/26.
//

#include "FileCache.hpp"

#include "AssetDirectory.hpp"
#include "Public/Core/Include.hpp"
#include "Public/IO/Include.hpp"

#include "AssetSerializer.hpp"

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

    std::vector<DirectoryAsset> FileCache::LoadAndGet(const Path& path) {
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
            else {
                AssetHeader header;
                bool isValidEngineAsset = false;

                // read file get header & validity of asset (engine asset or not)
                {
                    auto serializer = AssetSerializer::OpenSerializer(subPath, FileSystem::FileMode::READ);
                    isValidEngineAsset = AssetSerializer::ReadHeader(serializer, header);

                    AssetSerializer::CloseSerializer(serializer);
                }

                if (isValidEngineAsset) {
                    DirectoryAsset asset {
                        false,
                        subPath,
                        subPath.GetName().GetString(),
                        static_cast<AssetType>(header.Type),
                        AssetHandle::Null,
                        AssetHandle::Create(header.UUID)
                    };

                    result.push_back(asset);
                }
                else {
                    auto assetType = AssetDirectory::GetAssetTypeByExtension(subPath);

                    DirectoryAsset asset {
                        false,
                        subPath,
                        subPath.GetName().GetString(),
                        assetType,
                        AssetHandle::Null,
                        AssetHandle::Null,
                    };

                    result.push_back(asset);
                }

            }
        }

        Files.try_emplace(path, result);
        return result;
    }

    void FileCache::Clear() {
        Files.clear();
    }
}
