//
// Created by Akira Mujawar on 19/04/26.
//

#ifndef MEOWENGINE_REQUESTQUEUE_HPP
#define MEOWENGINE_REQUESTQUEUE_HPP

#include <RequestHandle.hpp>

namespace MeowEngine::Messaging {
    class RequestQueue {
    public:
        template<typename Request, typename Response>
        RequestHandle<Response> Send(Request request);
    };
}


#endif //MEOWENGINE_REQUESTQUEUE_HPP