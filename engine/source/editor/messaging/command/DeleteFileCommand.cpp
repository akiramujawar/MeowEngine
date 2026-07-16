//
// Created by Akira Mujawar on 16/07/26.
//

#include "DeleteFileCommand.hpp"

#include "AssetManager.hpp"
#include "MessageInitData.hpp"
#include "Public/IO/Include.hpp"

namespace MeowEngine::Messaging {

    void DeleteFileCommand::Execute(MessageInitData& context) {
        FileSystem::FileSystem::Remove(FilePath.CStr());

        context.AssetManager->RebuildDatabase();
    }

}