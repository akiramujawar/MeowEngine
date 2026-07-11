//
// Created by Akira Mujawar on 30/06/26.
//

#ifndef MEOWENGINE_PHYSICSLIFECYCLESYSTEM_HPP
#define MEOWENGINE_PHYSICSLIFECYCLESYSTEM_HPP

#include "IComponentSystem.hpp"

namespace MeowEngine::Runtime {
    class PhysicsEntitySystem : public IComponentSystem {
    public:
        void ProcessDirtyEntities(Asset::World& world) override;
        void Start(Asset::World& world) override {}
        void Update(Asset::World& world) override {};
        void Stop(Asset::World& world) override {}
    };
}


#endif //MEOWENGINE_PHYSICSLIFECYCLESYSTEM_HPP