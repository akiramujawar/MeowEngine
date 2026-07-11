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

    void RuntimeModule::Init(const RuntimeInitData context) {
        WorldManager.Init(&Gameplay);
        Context = context;
    }

    void RuntimeModule::SubscribeToEvents() {
        WorldManager.SubscribeToEvents();
        Gameplay.SubscribeToEvents();
    }

    void RuntimeModule::Load() {
        auto guid = MeowService().ConfigManager.SandboxConfig.LaunchWorldGuid;
        auto worldHandle = Asset::AssetHandle::Create(guid);

        WorldManager.Load(worldHandle, false);
        Gameplay.SetViewport(100, 100);
    }

    void RuntimeModule::Schedule(Threading::Scheduler& scheduler) {
        scheduler.AddTask(
            [this]() {
                PT_PROFILE_SCOPE_N("Gameplay Input");
                Gameplay.Input();
            }
        );

        scheduler.AddTask(
            [this]() {
                PT_PROFILE_SCOPE_N("Gameplay Update");
                Gameplay.Update();
            }
        );

        scheduler.AddTask(
            [this]() {
                PT_PROFILE_SCOPE_N("Physics Apply Results");
                if (Gameplay.GetIsSimulating()) {
                    PhysicsSynchronizer.ApplyResult(
                        Gameplay.GetWorld(),
                        Context.PhysicsResultBuffer->GetRead()
                    );
                }
            }
        );
    }

}
