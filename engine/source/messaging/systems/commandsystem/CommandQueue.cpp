//
// Created by Akira Mujawar on 19/04/26.
//

#include <CommandQueue.hpp>

#include "Scheduler.hpp"

namespace MeowEngine::Messaging {
    CommandQueue::CommandQueue() = default;
    CommandQueue::~CommandQueue() = default;

    void CommandQueue::Init(const MessageInitData& context) {
        Context = context;
    }

    void CommandQueue::Schedule(Threading::Scheduler& scheduler) {
        scheduler.AddTask([&]() {
            std::unique_ptr<ICommand> command;

            while (mainQueue.try_dequeue(command)) {
                command->Execute(Context);
            }
        });

        scheduler.AddTask([&]() {
            std::unique_ptr<ICommand> command;

            while (renderQueue.try_dequeue(command)) {
                command->Execute(Context);
            }
        });

        scheduler.AddTask([&]() {
            std::unique_ptr<ICommand> command;

            while (physicsQueue.try_dequeue(command)) {
                command->Execute(Context);
            }
        });
    }

    void CommandQueue::Push(ThreadType type, std::unique_ptr<ICommand> command) {
        switch (type) {
            case ThreadType::MAIN:
                mainQueue.enqueue(std::move(command));
                break;
            case ThreadType::RENDER:
                renderQueue.enqueue(std::move(command));
                break;
            case ThreadType::PHYSICS:
                physicsQueue.enqueue(std::move(command));
                break;
            default: ;
        }
    }

}
