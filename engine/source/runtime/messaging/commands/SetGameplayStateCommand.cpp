//
// Created by Akira Mujawar on 30/06/26.
//

#include "SetGameplayStateCommand.hpp"

#include <memory>

#include "MessageInitData.hpp"
#include "GameplayStateManager.hpp"

namespace MeowEngine::Messaging {

    void SetGameplayStateCommand::Execute(MessageInitData& context) {
        context.GameplayStateManager->SwitchState(State);
    }

}
