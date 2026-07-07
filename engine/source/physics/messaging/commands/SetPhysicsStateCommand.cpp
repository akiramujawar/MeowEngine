//
// Created by Akira Mujawar on 07/07/26.
//

#include "SetPhysicsStateCommand.hpp"

#include "MessageInitData.hpp"
#include "PhysicsSystem.hpp"

namespace MeowEngine::Messaging {

    void SetPhysicsStateCommand::Execute(MessageInitData& context) {
        // NOTE: we don't need physics state manager
        // we let main thread (in current case gameplay state manager be authorative)
        if (IsStart) {
            context.Physics->StartSimulation();
        }
        else {
            context.Physics->StopSimulation();
        }
    }

}
