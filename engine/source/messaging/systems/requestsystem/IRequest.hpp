//
// Created by Akira Mujawar on 19/04/26.
//

#ifndef MEOWENGINE_IREQUEST_HPP
#define MEOWENGINE_IREQUEST_HPP

#include "ThreadType.hpp"

namespace MeowEngine::Messaging {
    struct MessageInitData;

    class IRequest {
        friend class RequestQueue;

    public:
        virtual ~IRequest() = default;
        virtual bool ExecuteRequest(MessageInitData& context) = 0;
        virtual void ExecuteResponse(MessageInitData& context) = 0;

    public:
        [[nodiscard]] ThreadType GetRequestThreadType() const { return RequestThreadType; }
        [[nodiscard]] ThreadType GetResponseThreadType() const { return ResponseThreadType; }

    private:
        ThreadType RequestThreadType = ThreadType::NONE;
        ThreadType ResponseThreadType = ThreadType::NONE;
    };
}

#endif //MEOWENGINE_IREQUEST_HPP