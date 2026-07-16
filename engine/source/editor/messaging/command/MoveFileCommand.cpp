//
// Created by Akira Mujawar on 16/07/26.
//

#include "MoveFileCommand.hpp"

#include "AssetManager.hpp"
#include "MessageInitData.hpp"
#include "Public/Core/Include.hpp"
#include "Public/IO/Include.hpp"

namespace MeowEngine::Messaging {

    void MoveFileCommand::Execute(MessageInitData& context) {
        if(FileSystem::FileSystem::IsDirectory(MoveToPath.CStr())) {
            FileSystem::FileSystem::Move(Path(FilePath.GetRawString()), MoveToPath.CStr());

            context.AssetManager->RebuildDatabase();
        }
    }

}