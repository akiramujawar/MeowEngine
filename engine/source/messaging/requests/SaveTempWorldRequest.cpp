//
// Created by Akira Mujawar on 18/06/26.
//

#include "SaveTempWorldRequest.hpp"

#include "Public/Core/Include.hpp"
#include "FileDialog.hpp"
#include "MessageInitData.hpp"
#include "AssetManager.hpp"
#include "World.hpp"
#include "WorldManager.hpp"


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
    }
}
