//
// Created by Akira Mujawar on 24/06/26.
//

#include "FolderCache.hpp"

#include "Public/IO/Include.hpp"

namespace MeowEngine::Asset {
    void FolderCache::Bootstrap(const Path& sourcePath, const Path& shaderPath, const Path& assetPath) {
        SourcePath = sourcePath;
        ShaderPath = shaderPath;
        AssetPath = assetPath;
    }

    void FolderCache::Load() {
        FindFolders(SourcePath, SourceFolderMap);
        FindFolders(ShaderPath, ShaderFolderMap);
        FindFolders(AssetPath, AssetsFolderMap);
    }

    void FolderCache::FindFolders(const Path& path, FolderMap& folderMap) {
        const FileSystem::Directory directory { path };
        const auto directories = directory.GetDirectories(true);

        folderMap.try_emplace(path , DirectoryFolder{directories});

        for (auto& subPath : directories) {
            const auto subDirectory = FileSystem::Directory(subPath);
            const auto subDirectories = subDirectory.GetDirectories(false);

            folderMap.try_emplace(subPath , DirectoryFolder{subDirectories});
        }
    }
}
