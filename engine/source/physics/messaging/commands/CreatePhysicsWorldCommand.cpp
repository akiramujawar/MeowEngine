//
// Created by Akira Mujawar on 06/07/26.
//

#include "CreatePhysicsWorldCommand.hpp"

#include "MessageInitData.hpp"
#include "PhysicsSystem.hpp"

namespace MeowEngine::Messaging {

    void CreatePhysicsWorldCommand::Execute(MessageInitData& context) {
        context.Physics->CreateWorld(std::move(Data));
    }

}
