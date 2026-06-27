//
// Created by Akira Mujawar on 26/06/26.
//

#ifndef MEOWENGINE_TRANSFORMSYSTEM_HPP
#define MEOWENGINE_TRANSFORMSYSTEM_HPP


#include "IComponentSystem.hpp"

namespace MeowEngine::Runtime {
    class TransformSystem : public IComponentSystem{
    public:
        void Update(Asset::World& world) override;
    };
}


#endif //MEOWENGINE_TRANSFORMSYSTEM_HPP