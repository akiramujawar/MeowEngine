//
// Created by Akira Mujawar on 17/04/26.
//

#include <GameplaySystem.hpp>
#include <log.hpp>

#include "MeowService.hpp"
#include "EventBus.hpp"
#include "EventContainer.hpp"

// mandatory systems
#include "CameraSystem.hpp"

//
#include "CameraComponent.hpp"

namespace MeowEngine::Runtime {
    GameplaySystem::GameplaySystem() {
        MeowEngine::Log("GameplaySystem", "Constructed");

        CommonSystems.push_back(std::make_unique<CameraSystem>());
    }

    GameplaySystem::~GameplaySystem() {
        MeowEngine::Log("GameplaySystem", "Destructed");
    }

    void GameplaySystem::SubscribeToEvents() {
        MeowService().EventBus.Subscribe<Messaging::SceneViewportResizeEvent>(
          [&](const Messaging::SceneViewportResizeEvent& event) {
              SetViewport(event.Width, event.Height);
              // Runtime.GetGameplay().SetViewport(size.Width, size.Height);
              // Rendering::RenderCommand::SetViewportSize(event.Width, event.Height);
          }
      );
    }

    void GameplaySystem::SetWorld(Asset::World* world) {
        World = world;
    }

    Asset::World& GameplaySystem::GetWorld() {
        return *World;
    }

    void GameplaySystem::StartSimulation() {
        IsSimulating = true;
        IsPaused = false;

        // clear all dirty entities before starting, as we rebuild manually
        World->ClearDirtyEntities();

        // call to start, some systems build some systems simply start
        // for e.g. physics sync will filter through all rigidbody and create commands
        for (auto& system : SimulationSystems) {
            system->Start(*World);
        }
    }

    void GameplaySystem::PauseSimulation() {
        IsPaused = true;
    }

    void GameplaySystem::UnpauseSimulation() {
        IsPaused = false;
    }

    void GameplaySystem::StopSimulation() {
        IsSimulating = false;
        IsPaused = false;

        for (auto& system : SimulationSystems) {
            system->Stop(*World);
        }
    }

    void GameplaySystem::Input() {}

    void GameplaySystem::Update() const {
        // constantly update systems which are required even when simulation is inactive
        for (auto& system : CommonSystems) {
            system->Update(*World);
        }

        if (IsSimulating && !IsPaused) {
            // process all the dirty entities
            // for e.g. when rigidbody component is added, physics sync system processes that entity
            // to create a physics command
            for (auto& system : SimulationSystems) {
                system->ProcessDirtyEntities(*World);
            }

            // once processes clear dirty entities them
            World->ClearDirtyEntities();

            // update all the systems for live simulation
            // these include user added systems as well and is dynamic
            for (auto& system : SimulationSystems) {
                system->Update(*World);
            }
        }
    }

    void GameplaySystem::SetViewport(const float& width, const float& height) {
        Width = width;
        Height = height;

        ResetCamera();
    }

    void GameplaySystem::ResetCamera() const {
        GetCamera().SetViewport(Width, Height);
    }

    CameraComponent& GameplaySystem::GetCamera() const {
        return World->GetComponent<CameraComponent>(World->ActiveCamera);
    }
}
