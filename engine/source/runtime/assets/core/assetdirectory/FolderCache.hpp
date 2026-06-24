//
// Created by Akira Mujawar on 23/06/26.
//

#ifndef MEOWENGINE_FOLDERCACHE_HPP
#define MEOWENGINE_FOLDERCACHE_HPP

#include <unordered_map>

#include "Public/Core/Include.hpp"
#include "DirectoryFolder.hpp"

namespace MeowEngine::Asset {
    using FolderMap = std::unordered_map<Path, DirectoryFolder>;

    struct FolderCache {
        FolderCache() : SourcePath(""), ShaderPath(""), AssetPath("") {}

        void Bootstrap(const Path& sourcePath, const Path& shaderPath, const Path& assetPath);
        void Load();
        void FindFolders(const Path& path, FolderMap& folderMap);
        void Clear();

        FolderMap SourceFolderMap;
        FolderMap ShaderFolderMap;
        FolderMap AssetsFolderMap;

        Path SourcePath;
        Path ShaderPath;
        Path AssetPath;
    };
}

#endif //MEOWENGINE_FOLDERCACHE_HPP