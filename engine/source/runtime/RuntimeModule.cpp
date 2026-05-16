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

        // // TODO: come back when setting up AssetSystem
        // // Load & Switch to the world
        // WorldManager.Load();
        // WorldManager.Switch();


    }

    void RuntimeModule::Schedule(Threading::Scheduler& scheduler) {
        scheduler.AddTask(
            [this]() {
                Gameplay.Update();
            }
        );
    }

}
