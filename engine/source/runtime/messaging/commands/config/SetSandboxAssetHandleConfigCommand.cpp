//
// Created by Akira Mujawar on 29/06/26.
//

#include "SetSandboxAssetHandleConfigCommand.hpp"

#include "ConfigManager.hpp"
#include "MeowService.hpp"
#include "MessageInitData.hpp"
#include "reflection_macro_wrapper.hpp"

namespace MeowEngine::Messaging {

    void SetSandboxAssetHandleConfigCommand::Execute(MessageInitData& context) {
        MeowService().ConfigManager.SandboxConfig.GetConfig()["LaunchWorldGuid"] = WorldLaunchHandle.GetUUID();
        MeowService().ConfigManager.SandboxConfig.SaveConfig();
    }

}
