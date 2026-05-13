//
// Created by Akira Mujawar on 19/04/26.
//

#ifndef MEOWENGINE_THREADING_HPP
#define MEOWENGINE_THREADING_HPP

#include <Job.hpp>
#include <JobSystem.hpp>

#include <double_buffer.hpp>
#include <triple_buffer.hpp>

#include <scoped_atomic_access.hpp>
#include <thread_barrier.hpp>
#include <thread_pause.hpp>
#include <thread_wait.hpp>

namespace MeowEngine {
    namespace Threading = Core::Threading;

    using Core::Threading::Job;
    using Core::Threading::JobSystem;

}

#endif //MEOWENGINE_THREADING_HPP