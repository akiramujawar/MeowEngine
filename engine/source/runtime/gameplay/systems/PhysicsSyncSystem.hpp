//
// Created by Akira Mujawar on 30/06/26.
//

#ifndef MEOWENGINE_PHYSICSSYNCSYSTEM_HPP
#define MEOWENGINE_PHYSICSSYNCSYSTEM_HPP

#include "IComponentSystem.hpp"

namespace MeowEngine::Runtime {
    class PhysicsSyncSystem : public IComponentSystem {
    public:
        void ProcessDirtyEntities(Asset::World& world) override;
        void Start(Asset::World& world) override {}
        void Update(Asset::World& world) override {};
        void Stop(Asset::World& world) override {}
    };
}


#endif //MEOWENGINE_PHYSICSSYNCSYSTEM_HPP