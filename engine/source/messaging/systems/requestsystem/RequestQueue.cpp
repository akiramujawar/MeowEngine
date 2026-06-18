//
// Created by Akira Mujawar on 19/04/26.
//

#include "RequestQueue.hpp"

#include "Scheduler.hpp"

namespace MeowEngine::Messaging {
    void RequestQueue::Init(const MessageInitData& context) {
        Context = context;
    }

    void RequestQueue::Schedule(Threading::Scheduler& scheduler) {
        scheduler.AddTask([this]() {
            PollRequest(requestMainQueue);
            PollResponse(responseMainQueue);
        });

        scheduler.AddTask([this]() {
            PollRequest(requestRenderQueue);
            PollResponse(responseRenderQueue);
        });

        scheduler.AddTask([this]() {
            PollRequest(requestPhysicsQueue);
            PollResponse(responsePhysicsQueue);
        });
    }

    void RequestQueue::Push(ThreadType requestOn, ThreadType responseOn, std::unique_ptr<IRequest> request)  {
        // we assign the execution thread types so
        // that the response can execute on it's respective thread
        request->RequestThreadType = requestOn;
        request->ResponseThreadType = responseOn;

        // switch and set enqueue as per executeOn
        switch (requestOn) {
            case ThreadType::MAIN:
                requestMainQueue.enqueue(std::move(request));
                break;
            case ThreadType::RENDER:
                requestRenderQueue.enqueue(std::move(request));
                break;
            case ThreadType::PHYSICS:
                requestPhysicsQueue.enqueue(std::move(request));
                break;
            default: ;
        }
    }

    void RequestQueue::PollRequest(moodycamel::ConcurrentQueue<std::unique_ptr<IRequest>>& queue) {
        std::unique_ptr<IRequest> request;

        while (queue.try_dequeue(request)) {
            if (request->ExecuteRequest(Context)) {
                PushResponse(std::move(request));
            }
        }
    }

    void RequestQueue::PollResponse(moodycamel::ConcurrentQueue<std::unique_ptr<IRequest>>& queue) {
        std::unique_ptr<IRequest> response;

        while (queue.try_dequeue(response)) {
            response->ExecuteResponse(Context);
        }
    }

    void RequestQueue::PushResponse(std::unique_ptr<IRequest> request) {
        // switch and set enqueue as per executeOn
        switch (request->GetResponseThreadType()) {
            case ThreadType::MAIN:
                responseMainQueue.enqueue(std::move(request));
                break;
            case ThreadType::RENDER:
                responseRenderQueue.enqueue(std::move(request));
                break;
            case ThreadType::PHYSICS:
                responsePhysicsQueue.enqueue(std::move(request));
                break;
            default: ;
        }
    }
}
