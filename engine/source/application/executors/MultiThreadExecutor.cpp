//
// Created by Akira Mujawar on 17/04/26.
//

#include <MultiThreadExecutor.hpp>

namespace MeowEngine::Application {

    MultiThreadExecutor::MultiThreadExecutor(Threading::JobSystem& jobSystem)
        : JobSystem(jobSystem) {}

    void MultiThreadExecutor::Execute(Scheduler& scheduler) {
        for (const Job& job : scheduler.GetJobs()) {
            job.Task();
        }

        JobSystem.Wait();
    }

}
