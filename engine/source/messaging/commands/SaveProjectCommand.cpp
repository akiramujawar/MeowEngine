//
// Created by Akira Mujawar on 17/06/26.
//

#include "SaveProjectCommand.hpp"

#include "MeowService.hpp"
#include "WorldManager.hpp"

namespace MeowEngine::Messaging {
    void SaveProjectCommand::Execute(MessageInitData& context) {
        MeowService().WorldManager.Save();
        // trigger the save of imgui layout save from here?
    }
}
