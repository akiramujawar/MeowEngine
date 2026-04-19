//
// Created by Akira Mujawar on 17/04/26.
//

#ifndef MEOWENGINE_SINGLETHREADEXECUTOR_HPP
#define MEOWENGINE_SINGLETHREADEXECUTOR_HPP

#include <IExecutor.hpp>

namespace MeowEngine::Application {
    class SingleThreadExecutor : public IExecutor {
    public:
        void Execute(Scheduler& scheduler) override;
    };
}


#endif //MEOWENGINE_SINGLETHREADEXECUTOR_HPP