//
// Created by Akira Mujawar on 15/06/26.
//

#ifndef MEOWENGINE_ASSETDIRECTORY_HPP
#define MEOWENGINE_ASSETDIRECTORY_HPP

#include "Public/Core/Forward.hpp"
#include "Path.hpp" // for hash unordered_map

#include "FolderCache.hpp"
#include "FileCache.hpp"

namespace MeowEngine::Asset {
    /**
     * NOTE: use this for reading file system (in asset panel)
     */
    class AssetDirectory {
    public:
        AssetDirectory() = default;
        ~AssetDirectory() = default;

        void Init();
        void LoadAndBuild();
        void Rebuild();

        std::vector<DirectoryAsset> GetAssets(const Path& folderPath);
        static AssetType GetAssetTypeByExtension(const Path& path);

    public:
        // all directory paths
        FolderCache EngineFolderCache;
        FolderCache SandboxFolderCache;

        FileCache FileCache;
    };
}


#endif //MEOWENGINE_ASSETDIRECTORY_HPP