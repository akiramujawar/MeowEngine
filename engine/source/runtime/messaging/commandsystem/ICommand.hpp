//
// Created by Akira Mujawar on 19/04/26.
//

#ifndef MEOWENGINE_ICOMMAND_HPP
#define MEOWENGINE_ICOMMAND_HPP

#include <World.hpp>

namespace MeowEngine::Runtime::Messaging {
    struct ICommand {
        virtual ~ICommand() = default;
        virtual void Execute(World& world) = 0;
    };
}

#endif //MEOWENGINE_ICOMMAND_HPP