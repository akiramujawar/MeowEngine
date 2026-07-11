//
// Created by Akira Mujawar on 11/07/26.
//

#ifndef MEOWENGINE_DESTORYPHYSICSWORLDCOMMAND_HPP
#define MEOWENGINE_DESTORYPHYSICSWORLDCOMMAND_HPP

#include "ICommand.hpp"

namespace MeowEngine::Messaging {
    class DestroyPhysicsWorldCommand : public ICommand {
    public:
        DestroyPhysicsWorldCommand() {}

        void Execute(MessageInitData& context) override;

    };
}



#endif //MEOWENGINE_DESTORYPHYSICSWORLDCOMMAND_HPP