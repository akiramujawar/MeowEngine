//
// Created by Akira Mujawar on 30/06/26.
//

#ifndef MEOWENGINE_SETGAMEPLAYSTATECOMMAND_HPP
#define MEOWENGINE_SETGAMEPLAYSTATECOMMAND_HPP

#include <Public/Messaging/Include.hpp>

namespace MeowEngine::Messaging {
    enum class GameplayStateType {
        SIMULATE,
        PAUSE,
    };

    class SetGameplayStateCommand : public ICommand {
    public:
        explicit SetGameplayStateCommand(GameplayStateType type) {
            Type = type;
        }

        void Execute(MessageInitData& context) override;

    private:
        GameplayStateType Type;
    };
}



#endif //MEOWENGINE_SETGAMEPLAYSTATECOMMAND_HPP