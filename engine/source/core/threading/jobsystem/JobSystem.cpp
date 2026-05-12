//
// Created by Akira Mujawar on 17/04/26.
//

#include "JobSystem.hpp"

#include <log.hpp>

namespace MeowEngine::Core::Threading {
    JobSystem::JobSystem() : IsRunning(false), ActiveJobsCount(0) {
        MeowEngine::Log("JobSystem", "Constructed");
    }

    JobSystem::~JobSystem() {
        MeowEngine::Log("JobSystem", "Destructed");
    }

    void JobSystem::Start() {
        IsRunning = true;

        auto threadCount = std::thread::hardware_concurrency();

        for (unsigned i = 0; i < threadCount; i++) {
            Workers.emplace_back([this]() {
               Worker();
            });
        }
    }

    void JobSystem::Stop() {
        IsRunning = false;

        for (auto& worker : Workers) {
            worker.join();
        }
    }

    void JobSystem::Submit(Job job) {
        Queue.enqueue(job);
        ActiveJobsCount++;
    }

    void JobSystem::Dispatch(size_t jobCount, size_t jobPerGroup, std::function<void(size_t)> job) {
        if (jobCount == 0 || jobPerGroup == 0) {
            return;
        }

        uint32_t groupCount = (jobCount + jobPerGroup - 1) / jobPerGroup;

        for (size_t group = 0; group < groupCount; group++) {
            Submit(Job([=]() {
                const auto start = group * jobPerGroup;
                const auto end = start + jobPerGroup; // min (this , jobCount)

                for (uint32_t i = start; i < end; i++) {
                    job(i);
                }
            }));
        }
    }

    void JobSystem::Wait() {
        while (ActiveJobsCount > 0) {
            std::this_thread::yield();
        }
    }

    void JobSystem::Worker() {
        while (IsRunning) {
            Job job;

            if (!IsRunning) {
                return;
            }

            Queue.try_dequeue(job);

            job.Execute();

            ActiveJobsCount--;
        }
    }

}
