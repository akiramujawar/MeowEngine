//
// Created by Akira Mujawar on 17/04/26.
//

#ifndef MEOWENGINE_JOB_HPP
#define MEOWENGINE_JOB_HPP

#include <functional>

namespace MeowEngine::Core::Threading {
    struct Job {
        Job() = default;
        Job(std::function<void()> task);

        inline void Execute() const {
            if (Task) {
                Task();
            }
        }

        std::function<void()> Task;
    };
}


#endif //MEOWENGINE_JOB_HPP