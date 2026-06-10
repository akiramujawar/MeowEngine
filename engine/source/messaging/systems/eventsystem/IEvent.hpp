//
// Created by Akira Mujawar on 19/04/26.
//

#ifndef MEOWENGINE_IEVENT_HPP
#define MEOWENGINE_IEVENT_HPP

namespace MeowEngine::Messaging {
    struct IEvent {
        virtual ~IEvent() = default;
        virtual void Execute() = 0;
    };
}

#endif //MEOWENGINE_IEVENT_HPP