//
// Created by Akira Mujawar on 03/07/26.
//

#ifndef MEOWENGINE_REMOVEENTITYCOMMAND_HPP
#define MEOWENGINE_REMOVEENTITYCOMMAND_HPP


#include <Public/Messaging/Include.hpp>

#include "EntityHandle.hpp"

namespace MeowEngine::Messaging {
    class RemoveEntityCommand : public ICommand {
    public:
        RemoveEntityCommand(const Runtime::EntityHandle& handle) {
            Handle = handle;
        }

        void Execute(MessageInitData& context) override;

    private:
        Runtime::EntityHandle Handle;
    };
}


#endif //MEOWENGINE_REMOVEENTITYCOMMAND_HPP