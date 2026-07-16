//
// Created by Akira Mujawar on 09/07/26.
//

#include "CreateAssetCommand.hpp"

#include "MessageInitData.hpp"
#include <Public/IO.hpp>
#include "AssetManager.hpp"
#include "DefaultWorld.hpp"
#include "PhysicsMaterialAsset.hpp"

namespace MeowEngine::Messaging {

    void CreateAssetCommand::Execute(MessageInitData& context) {
        const Path path {DirectoryPath.GetRawString()};
        const Path assetName {AssetName.GetRawString()};
        Path assetPath = path + assetName;

        // create only if folder exists
        if (!path.Exists()) {
            return;
        }

        // create
        switch (Type) {
            case Asset::AssetType::FOLDER: {

                FileSystem::FileSystem::CreateDirectory(assetPath);

                break;
            }
            case Asset::AssetType::WORLD: {
                assetPath.ReplaceExtension(".meowdata");
                auto handle = context.AssetManager->CreateTempAsset<Runtime::DefaultWorld>();
                Asset::AssetManager::CreateAndSaveEmptyAsset(handle, Type, assetPath);
                context.AssetManager->SaveTempAsset<Asset::World>(handle, assetPath);

                break;
            }
            case Asset::AssetType::PHYSICS_MATERIAL: {
                assetPath.ReplaceExtension(".meowdata");
                auto handle = context.AssetManager->CreateTempAsset<Asset::PhysicsMaterialAsset>();
                Asset::AssetManager::CreateAndSaveEmptyAsset(handle, Type, assetPath);
                context.AssetManager->SaveTempAsset<Asset::PhysicsMaterialAsset>(handle, assetPath);

                break;
            }
            default:
                break;
        }

        context.AssetManager->RebuildDatabase();
    }

}
