//
// Created by Akira Mujawar on 15/05/26.
//

#include <PhysicsModule.hpp>

#include "Scheduler.hpp"
#include "Timing.hpp"

namespace MeowEngine::Physics {
    PhysicsModule::PhysicsModule() {}

    PhysicsModule::~PhysicsModule() {}

    void PhysicsModule::Init(const PhysicsInitData& context) {
        Physics.SetPhysics(PhysicsType::PHYSX);
    }

    void PhysicsModule::Schedule(Threading::Scheduler& scheduler) {
        // loop physics
        // extract into result
        // swap result

        // start simulation
        // create physics world
        // runtime create entity
        // create command after entity is created?

        // physics run's fixed timestep so extraction can be delayed?
        // or when result is consumed we extract
        scheduler.AddTask(
            [&]() {
                PT_PROFILE_SCOPE_N("Physics");
                Physics.Step(Timing.GetFixedDeltaTime());

                // TODO: later implement triple buffer
                Physics.FetchResult(Result.GetWrite());
                Result.Swap();

                Timing.Wait();
            }
        );
    }

}
