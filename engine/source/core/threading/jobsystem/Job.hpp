//
// Created by Akira Mujawar on 17/04/26.
//

#ifndef MEOWENGINE_JOB_HPP
#define MEOWENGINE_JOB_HPP

#include <functional>

namespace MeowEngine::Core::Threading {
    struct Job {
        std::function<void()> Task;
    };
}


#endif //MEOWENGINE_JOB_HPP