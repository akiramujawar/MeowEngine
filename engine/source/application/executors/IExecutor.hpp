//
// Created by Akira Mujawar on 17/04/26.
//

#ifndef MEOWENGINE_IEXECUTOR_HPP
#define MEOWENGINE_IEXECUTOR_HPP

#include <Threading.hpp>

namespace MeowEngine::Application {
    class IExecutor {
    public:
        // we might pass engine or each systems & similar old syncstate (something new to contain messaging system as well)
        virtual void Execute(Scheduler& scheduler) = 0;
        virtual ~IExecutor() = default;
    };
}


#endif //MEOWENGINE_IEXECUTOR_HPP