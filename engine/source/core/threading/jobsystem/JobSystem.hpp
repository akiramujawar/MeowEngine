//
// Created by Akira Mujawar on 17/04/26.
//

#ifndef MEOWENGINE_JOBSYSTEM_HPP
#define MEOWENGINE_JOBSYSTEM_HPP

#include <thread>
#include <concurrentqueue.h>
#include <functional>

#include <Job.hpp>

namespace MeowEngine::Core::Threading {
    /**
     * Executes parallel work
     * TODO: implement atomic, mutex, conditional_variable & wait conditions
     */
    class JobSystem {
    public:
        JobSystem();
        ~JobSystem();

        void Start();
        void Stop();

        /**
         * Add single task
         * @param job
         */
        void Submit(Job job);

        /**
         * Add task to be performed parallelly (like transform update per entity)
         * @param jobCount e.g. entity count
         * @param jobPerGroup task to be performed per job
         * @param job task
         */
        void Dispatch(
            size_t jobCount,
            size_t jobPerGroup,
            std::function<void(size_t)> job
        );

        void Wait();

    private:
        void Worker();

    private:
        std::vector<std::thread> Workers;
        moodycamel::ConcurrentQueue<Job> Queue;

        bool IsRunning;
        int ActiveJobsCount;
    };
}


#endif //MEOWENGINE_JOBSYSTEM_HPP