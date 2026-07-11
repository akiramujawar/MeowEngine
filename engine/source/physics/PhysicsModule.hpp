//
// Created by Akira Mujawar on 15/05/26.
//

#ifndef MEOWENGINE_PHYSICSMODULE_HPP
#define MEOWENGINE_PHYSICSMODULE_HPP



#include "PhysicsInitData.hpp"
#include "PhysicsSystem.hpp"
#include "PhysicsResultBuffer.hpp"
#include "FixedTiming.hpp"

namespace MeowEngine::Physics {


    class PhysicsModule {
    public:
        PhysicsModule();
        ~PhysicsModule();

        void Init(const PhysicsInitData& context);
        void Schedule(Threading::Scheduler& scheduler);

        PhysicsSystem& GetPhysics() { return Physics; }
        [[nodiscard]] PhysicsResultBuffer& GetResultBuffer() { return ResultBuffer; };

    private:
        PhysicsSystem Physics;
        PhysicsResultBuffer ResultBuffer;
        Core::FixedTiming Timing;
    };
}


#endif //MEOWENGINE_PHYSICSMODULE_HPP