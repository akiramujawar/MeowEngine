//
// Created by Akira Mujawar on 30/06/26.
//

#include "SetGameplayStateCommand.hpp"

#include "GameplaySystem.hpp"
#include "MessageInitData.hpp"
#include "WorldManager.hpp"

namespace MeowEngine::Messaging {

    void SetGameplayStateCommand::Execute(MessageInitData& context) {
        switch (Type) {
            case GameplayStateType::SIMULATE: {
                // stop and reset world
                if (context.Gameplay->GetIsSimulating()) {
                    context.Gameplay->StopSimulation();
                    context.WorldManager->ReloadActiveWorld();
                }
                // start
                else {
                    context.Gameplay->StartSimulation();
                }

                break;
            }
            case GameplayStateType::PAUSE: {
                if (context.Gameplay->GetIsSimulating()) {
                    // pause when simulating
                    if (context.Gameplay->GetIsPaused()) {
                        context.Gameplay->PauseSimulation();
                    }
                    // unpause when simulating
                    else {
                        context.Gameplay->UnpauseSimulation();
                    }
                }
                break;
            }
            default:
                break;
        }
    }

}
