//
// Created by Akira Mujawar on 17/04/26.
//

#include "SingleThreadExecutor.hpp"

namespace MeowEngine::Application {

    SingleThreadExecutor::SingleThreadExecutor() {
        MeowEngine::Log("SingleThreadExecutor", "Constructed");
    }

    SingleThreadExecutor::~SingleThreadExecutor() {
        MeowEngine::Log("SingleThreadExecutor", "Destructed");
    }

    void SingleThreadExecutor::Execute(Threading::Scheduler& scheduler) {
        PT_PROFILE_SCOPE;
        auto mainJobs = scheduler.GetMainJobs();
        auto renderJobs = scheduler.GetRenderJobs();
        auto physicsJobs = scheduler.GetPhysicsJobs();

        for (auto it = mainJobs.begin(); it != mainJobs.end(); ++it) {
            it->Execute();
        }

        for (auto it = physicsJobs.begin(); it != physicsJobs.end(); ++it) {
            it->Execute();
        }

        for (auto it = renderJobs.begin(); it != renderJobs.end(); ++it) {
            it->Execute();
        }
    }

}