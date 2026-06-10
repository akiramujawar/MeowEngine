//
// Created by Akira Mujawar on 19/04/26.
//

#include <CommandQueue.hpp>

namespace MeowEngine::Messaging {
    CommandQueue::CommandQueue() = default;
    CommandQueue::~CommandQueue() = default;

    void CommandQueue::Init(const MessageContext& context) {
        Context = context;
    }

    void CommandQueue::Push(std::unique_ptr<ICommand> command) {
        queue.enqueue(std::move(command));
    }

    void CommandQueue::Schedule(Threading::Scheduler& scheduler) {
        std::unique_ptr<ICommand> command;

        while (queue.try_dequeue(command)) {
            command->Execute(Context);
        }
    }

}
