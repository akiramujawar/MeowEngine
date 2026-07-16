//
// Created by Akira Mujawar on 16/07/26.
//

#include "RenameFileCommand.hpp"

#include "Public/Core/Include.hpp"
#include "Public/IO/Include.hpp"

namespace MeowEngine::Messaging {

    void RenameFileCommand::Execute(MessageInitData& context) {
        
        FileSystem::FileSystem::Rename(Path(FilePath.GetRawString()), Name.CStr());
    }

}