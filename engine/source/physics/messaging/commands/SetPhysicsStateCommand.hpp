//
// Created by Akira Mujawar on 07/07/26.
//

#ifndef MEOWENGINE_SETPHYSICSSIMULATIONSTATE_HPP
#define MEOWENGINE_SETPHYSICSSIMULATIONSTATE_HPP


#include "ICommand.hpp"
#include "PhysicsWorldData.hpp"

namespace MeowEngine::Messaging {
    class SetPhysicsStateCommand : public ICommand {
    public:
        SetPhysicsStateCommand(bool isStart) {
            IsStart = isStart;
        }

        void Execute(MessageInitData& context) override;

    private:
        bool IsStart;
    };
}


#endif //MEOWENGINE_SETPHYSICSSIMULATIONSTATE_HPP