//
// Created by Akira Mujawar on 17/04/26.
//

#include <Job.hpp>


namespace MeowEngine::Core::Threading {
    Job::Job(std::function<void()> task)
        : Task(std::move(task)){

    }
}
