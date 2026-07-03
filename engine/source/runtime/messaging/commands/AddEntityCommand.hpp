//
// Created by Akira Mujawar on 03/07/26.
//

#ifndef MEOWENGINE_ADDENTITYCOMMAND_HPP
#define MEOWENGINE_ADDENTITYCOMMAND_HPP


#include <Public/Messaging/Include.hpp>


namespace MeowEngine::Messaging {
    class AddEntityCommand : public ICommand {
    public:
        AddEntityCommand() {}

        void Execute(MessageInitData& context) override;

    private:
    };
}



#endif //MEOWENGINE_ADDENTITYCOMMAND_HPP