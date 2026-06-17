//
// Created by Akira Mujawar on 19/04/26.
//

#ifndef MEOWENGINE_COMMANDQUEUE_HPP
#define MEOWENGINE_COMMANDQUEUE_HPP

#include <concurrentqueue.h>

#include <Public/Threading/Forward.hpp>

#include <ICommand.hpp>
#include <MessageInitData.hpp>
#include "ThreadType.hpp"

namespace MeowEngine::Messaging {
    /**
     * Runs on owner thread & used at sync points. We maintain the order (very essential)
     * TODO: rename to something like ThreadCommandQueue or something similar since we will move to thread type structure
     */
    class CommandQueue {
    public:
        CommandQueue();
        ~CommandQueue();

        void Init(const MessageInitData& context);
        void Schedule(Threading::Scheduler& scheduler);

        void Push(ThreadType type, std::unique_ptr<ICommand> command);

    private:
        MessageInitData Context;

        moodycamel::ConcurrentQueue<std::unique_ptr<ICommand>> mainQueue;
        moodycamel::ConcurrentQueue<std::unique_ptr<ICommand>> renderQueue;
        moodycamel::ConcurrentQueue<std::unique_ptr<ICommand>> physicsQueue;
    };
}


#endif //MEOWENGINE_COMMANDQUEUE_HPP