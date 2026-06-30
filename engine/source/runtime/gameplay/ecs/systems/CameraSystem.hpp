//
// Created by Akira Mujawar on 26/06/26.
//

#ifndef MEOWENGINE_CAMERASYSTEM_HPP
#define MEOWENGINE_CAMERASYSTEM_HPP

#include "IComponentSystem.hpp"

namespace MeowEngine::Runtime {
    class CameraSystem : public IComponentSystem {
    public:
        void ProcessDirtyEntities(Asset::World& world) override {}
        void Start(Asset::World& world) override {}
        void Update(Asset::World& world) override;
        void Stop(Asset::World& world) override {}
    };
}


#endif //MEOWENGINE_CAMERASYSTEM_HPP