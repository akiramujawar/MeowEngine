//
// Created by Akira Mujawar on 06/07/26.
//

#include "GameplayStateManager.hpp"

#include "GameplaySystem.hpp"
#include "WorldManager.hpp"
#include "PhysicsWorldExtractor.hpp"

#include "CommandQueue.hpp"
#include "CreatePhysicsWorldCommand.hpp"
#include "SetPhysicsStateCommand.hpp"

namespace MeowEngine::Runtime {

    void GameplayStateManager::Init(const GameplayStateContext& context) {
        Context = context;
    }

    void GameplayStateManager::SwitchState(GameplayState state) {
        switch (state) {
            case GameplayState::SIMULATE: {
                // stop and reset world
                if (Context.Gameplay->GetIsSimulating()) {
                    Context.Gameplay->StopSimulation();
                    Context.WorldManager->ReloadActiveWorld();

                    // send command to physics to stop
                    Context.CommandQueue->Push(
                        Messaging::ThreadType::PHYSICS,
                        std::make_unique<Messaging::SetPhysicsStateCommand>(false)
                    );
                }
                // start
                else {
                    Context.Gameplay->StartSimulation();

                    // send command to start
                    // use physics extractor from runtime
                    auto data = std::make_unique<Physics::PhysicsWorldData>();

                    PhysicsWorldExtractor::Extract(Context.Gameplay->GetWorld(), *data);
                    // create a command
                    Context.CommandQueue->Push(
                        Messaging::ThreadType::PHYSICS,
                        std::make_unique<Messaging::CreatePhysicsWorldCommand>(std::move(data))
                    );

                    Context.CommandQueue->Push(
                        Messaging::ThreadType::PHYSICS,
                        std::make_unique<Messaging::SetPhysicsStateCommand>(true)
                    );
                }

                break;
            }
            case GameplayState::PAUSE: {
                if (Context.Gameplay->GetIsSimulating()) {
                    // pause when simulating
                    if (Context.Gameplay->GetIsPaused()) {
                        Context.Gameplay->PauseSimulation();

                        // send command to physics to pause
                        Context.CommandQueue->Push(
                            Messaging::ThreadType::PHYSICS,
                            std::make_unique<Messaging::SetPhysicsStateCommand>(false)
                        );
                    }
                    // unpause when simulating
                    else {
                        Context.Gameplay->UnpauseSimulation();

                        // send command to physics to unpause
                        Context.CommandQueue->Push(
                            Messaging::ThreadType::PHYSICS,
                            std::make_unique<Messaging::SetPhysicsStateCommand>(true)
                        );
                    }
                }
                break;
            }
            default:
                break;
        }
    }

}
