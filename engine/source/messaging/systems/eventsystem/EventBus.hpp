//
// Created by Akira Mujawar on 19/04/26.
//

#ifndef MEOWENGINE_EVENTBUS_HPP
#define MEOWENGINE_EVENTBUS_HPP

#include <functional>

namespace MeowEngine::Messaging {
    /**
     * Sometimes immediate or can be queued, random order. Normal event system we build similar to games
     */
    class EventBus {
    public:
        template <typename Type>
        void Publish(const Type& event);

        template <typename Type>
        void Subscribe(std::function<void(const Type&)> listener);
    };
}


#endif //MEOWENGINE_EVENTBUS_HPP