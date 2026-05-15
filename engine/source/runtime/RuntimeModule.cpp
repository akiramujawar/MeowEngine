//
// Created by Akira Mujawar on 15/05/26.
//

#include <RuntimeModule.hpp>

namespace MeowEngine::Runtime {
    RuntimeModule::RuntimeModule() {
        MeowEngine::Log("RuntimeModule", "Constructed");
    }

    RuntimeModule::~RuntimeModule() {
        MeowEngine::Log("RuntimeModule", "Destructed");
    }

    void RuntimeModule::Init() {
        WorldManager::Setup(&WorldManager, &Gameplay);

        // auto world = WorldManager.Load();

        // Gameplay.SetWorld(world);
    }

    void RuntimeModule::Schedule(Threading::Scheduler& scheduler) {
        scheduler.AddTask(
            [this]() {
                Gameplay.Update();
            }
        );
    }

}
