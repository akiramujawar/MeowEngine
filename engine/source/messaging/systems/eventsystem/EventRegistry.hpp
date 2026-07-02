//
// Created by Akira Mujawar on 02/07/26.
//

#ifndef MEOWENGINE_EVENTREGISTRY_HPP
#define MEOWENGINE_EVENTREGISTRY_HPP

#include <atomic>

#include "Event.hpp"

namespace MeowEngine::Messaging {
    /**
     * Tracks with a id for each Event (our events are pure data structs)
     */
    class EventRegistry {
    public:
        template<typename Type>
        static EventID Get() {
            static const EventID id = next++;
            return id;
        }

    private:
        inline static std::atomic<EventID> next{0};
    };
}

#endif //MEOWENGINE_EVENTREGISTRY_HPP