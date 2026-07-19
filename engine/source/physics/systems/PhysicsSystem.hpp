//
// Created by Akira Mujawar on 03/07/26.
//

#ifndef MEOWENGINE_PHYSICSSYSTEM_HPP
#define MEOWENGINE_PHYSICSSYSTEM_HPP

#include <memory>

#include "PhysicsResult.hpp"
#include "PhysXWorld.hpp"
#include "PhysicsType.hpp"
#include "PhysicsWorldData.hpp"

namespace MeowEngine::Physics {
    class PhysicsSystem {
    public:
        void SetPhysics(PhysicsType type);
        void Step(float inFixedDeltaTime) const;

        void StartSimulation();
        void StopSimulation();

        void FetchResult(PhysicsResult& result);
        void CreateWorld(std::unique_ptr<PhysicsWorldData> data);
        void DestroyWorld();

        bool GetIsSimulating() const { return IsSimulating; }

    private:
        std::unique_ptr<PhysXWorld> World;
        bool IsSimulating = false;
    };
}


#endif //MEOWENGINE_PHYSICSSYSTEM_HPP