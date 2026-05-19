//
// Created by Akira Mujawar on 19/04/26.
//

#ifndef MEOWENGINE_IREQUEST_HPP
#define MEOWENGINE_IREQUEST_HPP

namespace MeowEngine::Runtime::Messaging {
    struct IRequest {
        virtual ~IRequest() = default;
        virtual void Execute() = 0;
    };
}

#endif //MEOWENGINE_IREQUEST_HPP