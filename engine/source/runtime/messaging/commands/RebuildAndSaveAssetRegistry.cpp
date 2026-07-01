//
// Created by Akira Mujawar on 17/06/26.
//

#include "RebuildAndSaveAssetRegistry.hpp"

#include "MessageInitData.hpp"
#include "AssetManager.hpp"

namespace MeowEngine::Messaging {

    void RebuildAndSaveAssetRegistry::Execute(MessageInitData& context) {
        context.AssetManager->RebuildDatabase();
    }

}
