//
// Created by Akira Mujawar on 03/07/26.
//

#include "AddEntityCommand.hpp"

#include "GameplaySystem.hpp"
#include "MessageInitData.hpp"

namespace MeowEngine::Messaging {

    void AddEntityCommand::Execute(MessageInitData& context) {
        auto& world = context.Gameplay->GetWorld();

        world.AddEntity();
    }

}
