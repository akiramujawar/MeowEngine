//
// Created by Akira Mujawar on 17/04/26.
//

#ifndef MEOWENGINE_SCHEDULER_HPP
#define MEOWENGINE_SCHEDULER_HPP

#include <vector>
#include <functional>

#include <Job.hpp>
#include <Timing.hpp>

namespace MeowEngine::Core::Threading {
    /**
     * Decides jobs to run each frame (engine brain)
     */
    class Scheduler {
    public:
        Scheduler();
        ~Scheduler();

        void BuildFrameGraph(const Timing& timing);

        std::vector<Job>& GetMainJobs();
        std::vector<Job>& GetRenderJobs();
        std::vector<Job>& GetPhysicsJobs();

    private:
        Job CreateJob(const std::function<void()>& method);

        void BuildMainJobs();
        void BuildRenderJobs();
        void BuildPhysicsJobs();

    private:
        std::vector<Job> MainJobs;
        std::vector<Job> RenderJobs;
        std::vector<Job> PhysicsJobs;
    };
}


#endif //MEOWENGINE_SCHEDULER_HPP