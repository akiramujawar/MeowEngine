//
// Created by Akira Mujawar on 17/04/26.
//

#include <Scheduler.hpp>

#include <log.hpp>

namespace MeowEngine::Shared {
    Scheduler::Scheduler() {
        MeowEngine::Log("Scheduler", "Constructed");
    }

    Scheduler::~Scheduler() {
        MeowEngine::Log("Scheduler", "Destructed");
    }

    void Scheduler::BuildFrameGraph(const Core::Timing& timing) {
        MainJobs.clear();
        RenderJobs.clear();
        PhysicsJobs.clear();

        BuildMainJobs();
        BuildRenderJobs();
        BuildPhysicsJobs();
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

    Job Scheduler::CreateJob(const std::function<void()>& method) {
        Job job(method);

        return job;
    }


    void Scheduler::BuildMainJobs() {
        // CreateJob([this] {
        //    gameplaySystem.Update();
        // });
    }

    void Scheduler::BuildRenderJobs() {
        // CreateJob([this] {
        //    renderSystem.Render();
        // });
    }

    void Scheduler::BuildPhysicsJobs() {
        // CreateJob([this] {
        //    physicsSystem.Step();
        // });
    }


}
