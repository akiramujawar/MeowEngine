//
// Created by Akira Mujawar on 18/06/26.
//

#include "SaveWorldRequest.hpp"

#include "Public/Core/Include.hpp"
#include "FileDialog.hpp"
#include "MessageInitData.hpp"
#include "AssetManager.hpp"
#include "World.hpp"


namespace MeowEngine::Messaging {
    SaveWorldRequest::SaveWorldRequest(const Asset::AssetHandle& handle)
        : WorldHandle(handle) {}

    bool SaveWorldRequest::ExecuteRequest(MessageInitData& context) {
        context.FileDialog->ShowSaveDirectoryPopup(DirectoryPath);

        return true;
    }

    void SaveWorldRequest::ExecuteResponse(MessageInitData& context) {
        MeowEngine::Log("Save Directory Selected", DirectoryPath);
        auto path = Path(DirectoryPath);
        path.ReplaceExtension("meowdata");
        context.AssetManager->CreateAndSaveEmptyAsset(WorldHandle, Asset::AssetType::WORLD, path);
        context.AssetManager->SaveTempAsset<Asset::World>(WorldHandle, path);
    }
}
