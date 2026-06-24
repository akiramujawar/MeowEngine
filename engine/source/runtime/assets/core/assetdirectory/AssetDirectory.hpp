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
    class AssetDatabase;

    /**
     * NOTE: use this for reading file system (in asset panel)
     */
    class AssetDirectory {
    public:
        AssetDirectory() = default;
        ~AssetDirectory() = default;

        void Init(AssetDatabase& database);
        void Load();

        std::vector<DirectoryAsset> GetAssets(const Path& folderPath);

    public:
        // all directory paths
        FolderCache EngineFolderCache;
        FolderCache SandboxFolderCache;

        FileCache FileCache;

        AssetDatabase* Database;

        // write letters
        // directory setup
        // directory extraction
        // directory usage
        // import all files
        // serialization`
        // camera migration
        // navigation
        // shader pipeline
        // render resources
        // render pipeline

        // maths lib
        // physx

    };
}


#endif //MEOWENGINE_ASSETDIRECTORY_HPP