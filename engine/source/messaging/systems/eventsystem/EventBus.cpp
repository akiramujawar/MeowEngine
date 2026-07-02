//
// Created by Akira Mujawar on 19/04/26.
//

#include <EventBus.hpp>

#include "Public/Threading/Include.hpp"

namespace MeowEngine::Messaging {
    void EventBus::Schedule(Threading::Scheduler& scheduler) {
        scheduler.AddTask([this]() {
            Dispatch();
        });
    }
}