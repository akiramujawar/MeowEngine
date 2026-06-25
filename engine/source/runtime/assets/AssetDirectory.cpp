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
        const auto engineRootPath = MeowService().ConfigManager.Paths.GetEngineRootPath();
        const auto sandboxRootPath = MeowService().ConfigManager.Paths.GetSandboxRootPath();

        // const Path engineRootPath = "";
        // const Path sandboxRootPath = "";

        MeowEngine::Log("AssetDirectory::Load", {"EnginePath", engineRootPath.GetRawString()});
        MeowEngine::Log("AssetDirectory::Load", {"SandboxPath", sandboxRootPath.GetRawString()});

        EngineFolderCache.Bootstrap(
            engineRootPath + "engine/source",
            "engine/shaders",
            "engine/assets"
        );

        SandboxFolderCache.Bootstrap(
            sandboxRootPath + "source",
            "shaders",
            "assets"
        );

        EngineFolderCache.Load();
        SandboxFolderCache.Load();
    }

    void AssetDirectory::Rebuild() {
        EngineFolderCache.Clear();
        SandboxFolderCache.Clear();
        FileCache.Clear();

        EngineFolderCache.Load();
        SandboxFolderCache.Load();
    }

    std::vector<DirectoryAsset> AssetDirectory::GetAssets(const Path& folderPath) {
        if (FileCache.HasFile(folderPath)) {
            return FileCache.Get(folderPath);
        }
        else if (FileCache.IsValidFolder(folderPath)) {
            return FileCache.LoadAndGet(folderPath);
        }

        return {};
    }

    AssetType AssetDirectory::GetAssetTypeByExtension(const Path& path) {
        auto assetType = AssetType::UNKNOWN;
        if (path.GetExtension() == ".hpp") {
            assetType = AssetType::HPP;
        }
        else if (path.GetExtension() == ".cpp") {
            assetType = AssetType::CPP;
        }

        return assetType;
    }
}
