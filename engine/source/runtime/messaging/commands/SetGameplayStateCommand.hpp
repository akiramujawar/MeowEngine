//
// Created by Akira Mujawar on 30/06/26.
//

#ifndef MEOWENGINE_SETGAMEPLAYSTATECOMMAND_HPP
#define MEOWENGINE_SETGAMEPLAYSTATECOMMAND_HPP

#include <Public/Messaging/Include.hpp>
#include "GameplayState.hpp"

namespace MeowEngine::Messaging {
    class SetGameplayStateCommand : public ICommand {
    public:
        explicit SetGameplayStateCommand(Runtime::GameplayState state) {
            State = state;
        }

        void Execute(MessageInitData& context) override;

    private:
        Runtime::GameplayState State;
    };
}



#endif //MEOWENGINE_SETGAMEPLAYSTATECOMMAND_HPP