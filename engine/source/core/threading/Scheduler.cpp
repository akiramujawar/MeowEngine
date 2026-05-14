//
// Created by Akira Mujawar on 17/04/26.
//

#include <Scheduler.hpp>

#include <log.hpp>

namespace MeowEngine::Core::Threading {
    Scheduler::Scheduler() {
        MeowEngine::Log("Scheduler", "Constructed");
    }

    Scheduler::~Scheduler() {
        MeowEngine::Log("Scheduler", "Destructed");
    }

    void Scheduler::Clear() {
        MainJobs.clear();
    }

    std::vector<Job>& Scheduler::GetMainJobs() {
        return MainJobs;
    }

    std::vector<Job>& Scheduler::GetRenderJobs() {
        return RenderJobs;
    }

    std::vector<Job>& Scheduler::GetPhysicsJobs() {
        return PhysicsJobs;
    }

    void Scheduler::AddTask(const std::function<void()>& method) {
        Job job(method);

        MainJobs.push_back(job);
    }

}
