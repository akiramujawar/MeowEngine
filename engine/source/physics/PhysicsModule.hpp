//
// Created by Akira Mujawar on 15/05/26.
//

#ifndef MEOWENGINE_PHYSICSMODULE_HPP
#define MEOWENGINE_PHYSICSMODULE_HPP

#include <Public/Threading/Forward.hpp>

#include "PhysicsInitData.hpp"
#include "PhysicsSystem.hpp"
#include "PhysicsResult.hpp"
#include "FixedTiming.hpp"

namespace MeowEngine::Physics {
    class PhysicsModule {
    public:
        PhysicsModule();
        ~PhysicsModule();

        void Init(const PhysicsInitData& context);
        void Schedule(Threading::Scheduler& scheduler);

        PhysicsSystem& GetPhysics() { return Physics; }

    private:
        PhysicsSystem Physics;
        DoubleBuffer<PhysicsResult> Result;
        Core::FixedTiming Timing;
    };
}


#endif //MEOWENGINE_PHYSICSMODULE_HPP