//
// Created by Akira Mujawar on 17/04/26.
//

#ifndef MEOWENGINE_JOBSYSTEM_HPP
#define MEOWENGINE_JOBSYSTEM_HPP

#include <thread>
#include <concurrentqueue.h>

#include <Job.hpp>

namespace MeowEngine::Core::Threading {
    class JobSystem {
    public:
        void Submit(const Job& job);
        void Wait();

    private:
        std::vector<std::thread> Workers;
        moodycamel::ConcurrentQueue<Job> Queue;
    };
}


#endif //MEOWENGINE_JOBSYSTEM_HPP