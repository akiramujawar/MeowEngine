//
// Created by Akira Mujawar on 19/04/26.
//

#ifndef MEOWENGINE_ICOMMAND_HPP
#define MEOWENGINE_ICOMMAND_HPP

#include <memory>

namespace MeowEngine::Messaging {
    struct MessageInitData;

    struct ICommand {
        virtual ~ICommand() = default;
        virtual void Execute(MessageInitData& context) = 0;
    };
}

#endif //MEOWENGINE_ICOMMAND_HPP