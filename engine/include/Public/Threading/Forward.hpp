//
// Created by Akira Mujawar on 13/05/26.
//

#ifndef MEOWENGINE_THREADINGFWD_HPP
#define MEOWENGINE_THREADINGFWD_HPP

#include <double_buffer.hpp>
#include <triple_buffer.hpp>

namespace MeowEngine::Core::Threading {
    class Job;
    class JobSystem;
    class Scheduler;
}

namespace MeowEngine {
    namespace Threading = Core::Threading;

    // using Core::Threading::Job;
    // using Core::Threading::JobSystem;
    // using Core::Threading::Scheduler;

}

#endif //MEOWENGINE_THREADINGFWD_HPP