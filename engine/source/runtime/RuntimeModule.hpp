//
// Created by Akira Mujawar on 15/05/26.
//

#ifndef MEOWENGINE_RUNTIMEMODULE_HPP
#define MEOWENGINE_RUNTIMEMODULE_HPP

#include <GameplaySystem.hpp>
// #include <PhysicsSystem.hpp>
// #include <RenderSystem.hpp>

namespace MeowEngine::Runtime {
    class RuntimeModule {
    public:
        // systems
        Runtime::GameplaySystem Gameplay;
        // Runtime::PhysicsSystem PhysicsSystem;
        // Runtime::RenderSystem RenderSystem;
    };
}


#endif //MEOWENGINE_RUNTIMEMODULE_HPP