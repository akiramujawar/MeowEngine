//
// Created by Akira Mujawar on 02/07/26.
//

#ifndef MEOWENGINE_LISTENER_HPP
#define MEOWENGINE_LISTENER_HPP

#include <functional>

namespace MeowEngine::Messaging {
    /**
     * Method callback is stored in listener list (i.e. subscribers)
     * these methods recieve the EventData and called at the
     * time of dispatch
     */
    using Listener = std::function<void(const void*)>;
}

#endif //MEOWENGINE_LISTENER_HPP