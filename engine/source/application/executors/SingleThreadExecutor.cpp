//
// Created by Akira Mujawar on 17/04/26.
//

#include "SingleThreadExecutor.hpp"

namespace MeowEngine::Application {

    void SingleThreadExecutor::Execute(Scheduler& scheduler) {
        for (const Job& job : scheduler.GetJobs()) {
            job.Task();
        }
    }

}