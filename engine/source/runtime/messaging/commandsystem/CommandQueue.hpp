//
// Created by Akira Mujawar on 19/04/26.
//

#ifndef MEOWENGINE_COMMANDQUEUE_HPP
#define MEOWENGINE_COMMANDQUEUE_HPP

#include <World.hpp>
#include <ICommand.hpp>

namespace MeowEngine::Runtime::Messaging {
    /**
     * Runs on owner thread & used at sync points. We maintain the order (very essential)
     */
    class CommandQueue {
    public:
        void Push(std::unique_ptr<ICommand> command);
        void ExecuteAll(World& world);
    };
}


#endif //MEOWENGINE_COMMANDQUEUE_HPP