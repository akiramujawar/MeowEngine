//
// Created by Akira Mujawar on 15/06/26.
//

#include "AssetDirectory.hpp"

#include "Public/IO/Include.hpp"
#include "MeowService.hpp"
#include "ConfigManager.hpp"

namespace MeowEngine::Asset {
    void AssetDirectory::Init() {}

    // ReSharper disable once CppMemberFunctionMayBeStatic
    void AssetDirectory::Load() {
        const auto engineRootPath = MeowService().Project.Paths.GetEngineRootPath();
        const auto sandboxRootPath = MeowService().Project.Paths.GetSandboxRootPath();

        MeowEngine::Log("AssetDirectory::Load", {"EnginePath", engineRootPath.GetRawString()});
        MeowEngine::Log("AssetDirectory::Load", {"SandboxPath", sandboxRootPath.GetRawString()});

        FindFolders(engineRootPath + "engine/source", EngineSourceFolderMap);
        FindFolders(engineRootPath + "engine/shaders", EngineShaderFolderMap);
        FindFolders(engineRootPath + "engine/assets", EngineAssetsFolderMap);

        FindFolders(sandboxRootPath + "source", SandboxSourceFolderMap);
        FindFolders(sandboxRootPath + "shaders", SandboxShaderFolderMap);
        FindFolders(sandboxRootPath + "assets", SandboxAssetsFolderMap);

    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    void AssetDirectory::FindFolders(const Path& path, FolderMap& folderMap) {
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
