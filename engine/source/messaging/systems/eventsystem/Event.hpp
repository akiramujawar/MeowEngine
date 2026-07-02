//
// Created by Akira Mujawar on 02/07/26.
//

#ifndef MEOWENGINE_EVENT_HPP
#define MEOWENGINE_EVENT_HPP

#include <cstdlib>
#include <memory>

namespace MeowEngine::Messaging {
    /**
     * Each event struct is given a EventID
     */
    using EventID = uint32_t;

    /**
     * Stores event ID & the event struct data
     * Used while queuing up events in EventBus
     */
    struct Event {
        EventID ID {};
        std::shared_ptr<void> Data;
    };
}

#endif //MEOWENGINE_EVENT_HPP