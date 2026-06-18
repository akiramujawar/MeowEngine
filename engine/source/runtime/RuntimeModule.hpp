//
// Created by Akira Mujawar on 15/05/26.
//

#ifndef MEOWENGINE_RUNTIMEMODULE_HPP
#define MEOWENGINE_RUNTIMEMODULE_HPP

#include <Public/Threading/Forward.hpp>

#include <WorldManager.hpp>
#include <GameplaySystem.hpp>

#include <PhysicsCommand.hpp>

namespace MeowEngine::Runtime {
    struct RuntimeInitData;

    class RuntimeModule {
    public:
        RuntimeModule();
        ~RuntimeModule();

        void Init(RuntimeInitData& context);
        void Load();
        void Schedule(Threading::Scheduler& scheduler);

        WorldManager& GetWorldManager() { return WorldManager; };
        GameplaySystem& GetGameplay() { return Gameplay; };

    private:
        WorldManager WorldManager;
        GameplaySystem Gameplay;

        DoubleBuffer<Physics::PhysicsCommand> PhysicsSnapshot;
    };
}


#endif //MEOWENGINE_RUNTIMEMODULE_HPP