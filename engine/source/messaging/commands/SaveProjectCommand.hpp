//
// Created by Akira Mujawar on 17/06/26.
//

#ifndef MEOWENGINE_SAVEPROJECTCOMMAND_HPP
#define MEOWENGINE_SAVEPROJECTCOMMAND_HPP


#include <Public/Messaging/Include.hpp>


namespace MeowEngine::Messaging {
    class SaveProjectCommand  : public ICommand {
    public:
        SaveProjectCommand() = default;

        void Execute(MessageInitData& context) override;
    };
}


#endif //MEOWENGINE_SAVEPROJECTCOMMAND_HPP