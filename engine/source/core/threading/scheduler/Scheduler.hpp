//
// Created by Akira Mujawar on 17/04/26.
//

#ifndef MEOWENGINE_SCHEDULER_HPP
#define MEOWENGINE_SCHEDULER_HPP

#include <vector>

#include <Job.hpp>
#include <Timing.hpp>

namespace MeowEngine::Core::Threading {
    class Scheduler {
    public:
        void BuildFrameGraph(const Timing& timing);

        const std::vector<Job>& GetJobs() const;

    private:
        std::vector<Job> Jobs;
    };
}


#endif //MEOWENGINE_SCHEDULER_HPP