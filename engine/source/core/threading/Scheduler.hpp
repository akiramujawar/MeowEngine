//
// Created by Akira Mujawar on 17/04/26.
//

#ifndef MEOWENGINE_SCHEDULER_HPP
#define MEOWENGINE_SCHEDULER_HPP

#include <vector>
#include <functional>

#include <Threading.hpp>
#include <Timing.hpp>

namespace MeowEngine::Core::Threading {
    /**
     * Decides tasks to run each frame (engine brain)
     */
    class Scheduler {
    public:
        Scheduler();
        ~Scheduler();

        std::vector<Job>& GetMainJobs();
        std::vector<Job>& GetRenderJobs();
        std::vector<Job>& GetPhysicsJobs();

        void AddTask(const std::function<void()>& method);

    private:
        std::vector<Job> MainJobs;
        std::vector<Job> RenderJobs;
        std::vector<Job> PhysicsJobs;
    };
}


#endif //MEOWENGINE_SCHEDULER_HPP