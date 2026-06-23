//
// Created by Akira Mujawar on 15/06/26.
//

#ifndef MEOWENGINE_ASSETDIRECTORY_HPP
#define MEOWENGINE_ASSETDIRECTORY_HPP

#include <map>

#include "Public/Core/Forward.hpp"
#include "Path.hpp" // for hash unordered_map

#include "DirectoryFolder.hpp"

namespace MeowEngine::Asset {
    /**
     * NOTE: use this for reading file system (in asset panel)
     */
    class AssetDirectory {
        using FolderMap = std::unordered_map<Path, DirectoryFolder>;

    public:
        AssetDirectory() = default;
        ~AssetDirectory() = default;

        void Init();
        void Load();

        std::vector<std::string> GetAssets(std::string directoryPaths);

    private:
        void FindFolders(const Path& path, FolderMap& folderMap);

    private:
        // all directory paths and assets inside them
        FolderMap EngineSourceFolderMap;
        FolderMap EngineShaderFolderMap;
        FolderMap EngineAssetsFolderMap;

        FolderMap SandboxSourceFolderMap;
        FolderMap SandboxShaderFolderMap;
        FolderMap SandboxAssetsFolderMap;

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