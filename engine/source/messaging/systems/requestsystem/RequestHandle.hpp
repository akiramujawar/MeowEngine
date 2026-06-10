//
// Created by Akira Mujawar on 19/04/26.
//

#ifndef MEOWENGINE_REQUESTHANDLE_HPP
#define MEOWENGINE_REQUESTHANDLE_HPP

#include <atomic>

namespace MeowEngine::Messaging {
    /**
     * Useful for cross-thread messaging, goes to owner threads, response is async
     * @tparam Type
     */
    template <typename Type>
    struct RequestHandle {
        std::atomic<bool> Ready = false;
        Type Result;
    };
}


#endif //MEOWENGINE_REQUESTHANDLE_HPP