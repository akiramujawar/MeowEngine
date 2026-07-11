//
// Created by Akira Mujawar on 11/07/26.
//

#include "DestroyPhysicsWorldCommand.hpp"

#include "MessageInitData.hpp"
#include "PhysicsSystem.hpp"

namespace MeowEngine::Messaging {

    void DestroyPhysicsWorldCommand::Execute(MessageInitData& context) {
        context.Physics->DestroyWorld();
    }

}
