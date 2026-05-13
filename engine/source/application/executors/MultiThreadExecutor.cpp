//
// Created by Akira Mujawar on 17/04/26.
//

#include <MultiThreadExecutor.hpp>

namespace MeowEngine::Application {

    MultiThreadExecutor::MultiThreadExecutor(Threading::JobSystem& jobSystem)
        : JobSystem(jobSystem) {}

    void MultiThreadExecutor::Execute(Threading::Scheduler& scheduler) {
        // NOTE: use job system to dispatch the scheduled tasks
        auto jobs = scheduler.GetMainJobs();

        for (auto it = jobs.begin(); it != jobs.end(); ++it) {
            it->Execute();
        }
    }

}
