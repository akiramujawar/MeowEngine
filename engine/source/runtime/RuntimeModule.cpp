//
// Created by Akira Mujawar on 15/05/26.
//

#include <RuntimeModule.hpp>

#include <Public/Threading/Include.hpp>
#include <log.hpp>

#include "MeowService.hpp"
#include "ConfigManager.hpp"

namespace MeowEngine::Runtime {
    RuntimeModule::RuntimeModule() {
        MeowEngine::Log("RuntimeModule", "Constructed");
    }

    RuntimeModule::~RuntimeModule() {
        MeowEngine::Log("RuntimeModule", "Destructed");
    }

    void RuntimeModule::Init(RuntimeInitData& context) {
        WorldManager.Init(&Gameplay);
    }

    void RuntimeModule::Load() {
        WorldManager.Load(MeowService().Project.SandboxConfig.LaunchWorldHandle);
    }

    void RuntimeModule::Schedule(Threading::Scheduler& scheduler) {
        scheduler.AddTask(
            [this]() {
                Gameplay.Input();
            }
        );

        scheduler.AddTask(
            [this]() {
                Gameplay.Update();
            }
        );
    }

}
