//
// Created by Akira Mujawar on 19/04/26.
//

#ifndef MEOWENGINE_REQUESTQUEUE_HPP
#define MEOWENGINE_REQUESTQUEUE_HPP

#include <memory>
#include <concurrentqueue.h>

#include "Public/Threading/Forward.hpp"

#include "MessageInitData.hpp"
#include "IRequest.hpp"


namespace MeowEngine::Messaging {
    class RequestQueue {
    public:
        RequestQueue() = default;
        ~RequestQueue() = default;

        void Init(const MessageInitData& context);
        void Schedule(Threading::Scheduler& scheduler);

        void Push(ThreadType requestOn, ThreadType responseOn, std::unique_ptr<IRequest> request);

    private:
        void PollRequest(moodycamel::ConcurrentQueue<std::unique_ptr<IRequest>>& queue);
        void PollResponse(moodycamel::ConcurrentQueue<std::unique_ptr<IRequest>>& queue);
        void PushResponse(std::unique_ptr<IRequest> request);

        MessageInitData Context = {};

        moodycamel::ConcurrentQueue<std::unique_ptr<IRequest>> requestMainQueue;
        moodycamel::ConcurrentQueue<std::unique_ptr<IRequest>> requestRenderQueue;
        moodycamel::ConcurrentQueue<std::unique_ptr<IRequest>> requestPhysicsQueue;

        moodycamel::ConcurrentQueue<std::unique_ptr<IRequest>> responseMainQueue;
        moodycamel::ConcurrentQueue<std::unique_ptr<IRequest>> responseRenderQueue;
        moodycamel::ConcurrentQueue<std::unique_ptr<IRequest>> responsePhysicsQueue;

    };
}


#endif //MEOWENGINE_REQUESTQUEUE_HPP