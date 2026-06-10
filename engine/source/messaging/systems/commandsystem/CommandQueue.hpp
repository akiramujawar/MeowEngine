//
// Created by Akira Mujawar on 19/04/26.
//

#ifndef MEOWENGINE_COMMANDQUEUE_HPP
#define MEOWENGINE_COMMANDQUEUE_HPP

#include <concurrentqueue.h>

#include <Public/Threading/Forward.hpp>

#include <ICommand.hpp>
#include <MessageContext.hpp>

namespace MeowEngine::Messaging {
    /**
     * Runs on owner thread & used at sync points. We maintain the order (very essential)
     */
    class CommandQueue {
    public:
        CommandQueue();
        ~CommandQueue();

        void Init(const MessageContext& context);
        void Schedule(Threading::Scheduler& scheduler);

        void Push(std::unique_ptr<ICommand> command);

    private:
        MessageContext Context;
        moodycamel::ConcurrentQueue<std::unique_ptr<ICommand>> queue;
    };
}


#endif //MEOWENGINE_COMMANDQUEUE_HPP