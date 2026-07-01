//
// Created by Akira Mujawar on 18/06/26.
//

#include "LoadWorldCommand.hpp"

#include "MessageInitData.hpp"
#include "AssetManager.hpp"
#include "WorldManager.hpp"

namespace MeowEngine::Messaging {

    void LoadWorldCommand::Execute(MessageInitData& context) {
        context.AssetManager->UnloadAsset(WorldHandle);
        context.WorldManager->Load(WorldHandle);
    }

}
