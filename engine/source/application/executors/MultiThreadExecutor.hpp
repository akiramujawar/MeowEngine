//
// Created by Akira Mujawar on 17/04/26.
//

#ifndef MEOWENGINE_MULTITHREADEXECUTOR_HPP
#define MEOWENGINE_MULTITHREADEXECUTOR_HPP

#include <IExecutor.hpp>
#include <Threading.hpp>

#include <MainThread.hpp>
#include <RenderThread.hpp>
#include <PhysicsThread.hpp>

namespace MeowEngine::Application {
    class MultiThreadExecutor : public IExecutor {
    public:
        explicit MultiThreadExecutor(Threading::JobSystem& jobSystem);

        void Execute(Shared::Scheduler& scheduler) override;

    private:
        JobSystem& JobSystem;

        MainThread MainThread;
        RenderThread RenderThread;
        PhysicsThread PhysicsThread;
    };
}


#endif //MEOWENGINE_MULTITHREADEXECUTOR_HPP