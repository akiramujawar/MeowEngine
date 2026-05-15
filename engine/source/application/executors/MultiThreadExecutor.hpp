//
// Created by Akira Mujawar on 17/04/26.
//

#ifndef MEOWENGINE_MULTITHREADEXECUTOR_HPP
#define MEOWENGINE_MULTITHREADEXECUTOR_HPP

#include <IExecutor.hpp>
#include <Public/Threading/Forward.hpp>

#include <MainThread.hpp>
#include <RenderThread.hpp>
#include <PhysicsThread.hpp>

namespace MeowEngine::Application {
    /**
     * Runs the jobs parallelly using JobSystem
     * e.g. used for macOS, windows builds etc...
     */
    class MultiThreadExecutor : public IExecutor {
    public:
        explicit MultiThreadExecutor(Threading::JobSystem& jobSystem);
        ~MultiThreadExecutor();

        /**
         * Called every frame from Engine to run jobs
         * @param scheduler
         */
        void Execute(Threading::Scheduler& scheduler) override;

    private:
        Threading::JobSystem& JobSystem;

        MainThread MainThread;
        RenderThread RenderThread;
        PhysicsThread PhysicsThread;
    };
}


#endif //MEOWENGINE_MULTITHREADEXECUTOR_HPP