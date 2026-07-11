//
// Created by Akira Mujawar on 11/07/26.
//

#ifndef MEOWENGINE_PHYSICSSYNCHRONIZER_HPP
#define MEOWENGINE_PHYSICSSYNCHRONIZER_HPP

#include "PhysicsResult.hpp"
#include "World.hpp"

namespace MeowEngine::Runtime {
    class PhysicsSynchronizer {
    public:
        void ApplyResult(Asset::World& world, const Physics::PhysicsResult& result);
    };
}


#endif //MEOWENGINE_PHYSICSSYNCHRONIZER_HPP