//
// Created by Akira Mujawar on 19/04/26.
//

#ifndef MEOWENGINE_EVENTBUS_HPP
#define MEOWENGINE_EVENTBUS_HPP

#include <queue>
#include <shared_mutex>
#include <concurrentqueue.h>

#include "Public/Threading/Forward.hpp"
#include "Event.hpp"
#include "Listener.hpp"
#include "EventRegistry.hpp"

namespace MeowEngine::Messaging {
    /**
     * Queued events (subscribe on Main thread, Enqueue from any thread)
     */
    class EventBus {
    public:
        void Schedule(Threading::Scheduler& scheduler);

        template <typename Type>
        void Enqueue(const Type& event) {
            EventQueue.enqueue({
                EventRegistry::Get<Type>(),
                std::make_shared<Type>(event)
            });
        }

        template <typename Type>
        void Subscribe(const std::function<void(const Type&)>& listener) {
            std::unique_lock lock(ListenersMutex);

            auto id = EventRegistry::Get<Type>();
            Listeners[id].push_back(
                [listener](const void* data) {
                    listener(*static_cast<const Type*>(data));
                }
            );
        }

        void Dispatch() {
            Event event;

            while (EventQueue.try_dequeue(event)) {
                std::shared_lock lock(ListenersMutex);

                auto& listeners = Listeners[event.ID];
                for (auto& listener : listeners) {
                    listener(event.Data.get());
                }
            }
        }

    private:
        /**
         * All the list of classes who have subscribed, they wait and listen to any event emitted
         * Subcribers will recieve events they are listening
         * i.e. event structs are separated by EventID
         */
        std::unordered_map<EventID, std::vector<Listener>> Listeners;
        mutable std::shared_mutex ListenersMutex;

        /**
         * All the events which need to be processed are cached here
         * (emitted events)
         */
        moodycamel::ConcurrentQueue<Event> EventQueue;
    };
}


#endif //MEOWENGINE_EVENTBUS_HPP