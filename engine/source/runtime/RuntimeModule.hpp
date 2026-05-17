//
// Created by Akira Mujawar on 15/05/26.
//

#ifndef MEOWENGINE_RUNTIMEMODULE_HPP
#define MEOWENGINE_RUNTIMEMODULE_HPP

#include <Public/Threading/Forward.hpp>

#include <WorldManager.hpp>
#include <GameplaySystem.hpp>

#include <RenderSnapshot.hpp>
#include <PhysicsCommand.hpp>

namespace MeowEngine::Runtime {
    class RuntimeModule {
    public:
        RuntimeModule();
        ~RuntimeModule();

        void Init();
        void Schedule(Threading::Scheduler& scheduler);

    private:
        WorldManager WorldManager;
        GameplaySystem Gameplay;
    };
}


#endif //MEOWENGINE_RUNTIMEMODULE_HPP