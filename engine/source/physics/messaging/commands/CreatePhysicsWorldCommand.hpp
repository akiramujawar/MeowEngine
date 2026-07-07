//
// Created by Akira Mujawar on 06/07/26.
//

#ifndef MEOWENGINE_CREATEPHYSICSWORLDCOMMAND_HPP
#define MEOWENGINE_CREATEPHYSICSWORLDCOMMAND_HPP

#include "memory"

#include "ICommand.hpp"
#include "PhysicsWorldData.hpp"

namespace MeowEngine::Messaging {
    class CreatePhysicsWorldCommand : public ICommand {
    public:
        CreatePhysicsWorldCommand(std::unique_ptr<Physics::PhysicsWorldData> data) {
            Data = std::move(data);
        }

        void Execute(MessageInitData& context) override;

    private:
        std::unique_ptr<Physics::PhysicsWorldData> Data;
    };
}


#endif //MEOWENGINE_CREATEPHYSICSWORLDCOMMAND_HPP