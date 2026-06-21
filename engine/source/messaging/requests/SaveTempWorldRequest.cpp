//
// Created by Akira Mujawar on 18/06/26.
//

#include "SaveTempWorldRequest.hpp"

#include "Public/Core/Include.hpp"
#include "FileDialog.hpp"
#include "MessageInitData.hpp"
#include "AssetManager.hpp"
#include "World.hpp"


namespace MeowEngine::Messaging {
    SaveTempWorldRequest::SaveTempWorldRequest(const Asset::AssetHandle& handle)
        : WorldHandle(handle) {}

    bool SaveTempWorldRequest::ExecuteRequest(MessageInitData& context) {
        context.FileDialog->ShowSaveDirectoryPopup(DirectoryPath);

        return true;
    }

    void SaveTempWorldRequest::ExecuteResponse(MessageInitData& context) {
        MeowEngine::Log("Save Directory Selected", DirectoryPath);
        auto path = Path(DirectoryPath);
        path.ReplaceExtension("meowdata");

        context.AssetManager->CreateAndSaveEmptyAsset(WorldHandle, Asset::AssetType::WORLD, path);
        auto handle = context.AssetManager->SaveTempAsset<Asset::World>(WorldHandle, path);

        // for testing
        // since for dynamic loading we need build asset directory and use it in asset panel
        context.AssetManager->UnloadAsset(handle);
        context.AssetManager->LoadAsset<Asset::World>(handle);
    }
}
