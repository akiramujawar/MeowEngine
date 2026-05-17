//
// Created by Akira Mujawar on 15/05/26.
//

#ifndef MEOWENGINE_PHYSICSMODULE_HPP
#define MEOWENGINE_PHYSICSMODULE_HPP

#include <Public/Threading/Forward.hpp>

#include <PhysicsSystem.hpp>
#include <PhysicsResult.hpp>

namespace MeowEngine::Physics {
    class PhysicsModule {
    public:
        PhysicsModule();
        ~PhysicsModule();

        void Init();
        void Schedule(Threading::Scheduler& scheduler);

    private:
        PhysicsSystem PhysicsSystem;

        DoubleBuffer<PhysicsResult> Result;
    };
}


#endif //MEOWENGINE_PHYSICSMODULE_HPP