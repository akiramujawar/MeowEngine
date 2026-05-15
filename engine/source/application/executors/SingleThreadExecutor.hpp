//
// Created by Akira Mujawar on 17/04/26.
//

#ifndef MEOWENGINE_SINGLETHREADEXECUTOR_HPP
#define MEOWENGINE_SINGLETHREADEXECUTOR_HPP

#include <IExecutor.hpp>

namespace MeowEngine::Application {
    /**
     * Runs all the jobs sequentially on existing thread
     * e.g. used for web builds
     */
    class SingleThreadExecutor : public IExecutor {
    public:
        SingleThreadExecutor();
        ~SingleThreadExecutor();

        /**
         * Called every frame from Engine to run jobs
         * @param scheduler
         */
        void Execute(Threading::Scheduler& scheduler) override;
    };
}


#endif //MEOWENGINE_SINGLETHREADEXECUTOR_HPP