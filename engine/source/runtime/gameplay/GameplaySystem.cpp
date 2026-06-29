//
// Created by Akira Mujawar on 17/04/26.
//

#include <GameplaySystem.hpp>
#include <log.hpp>

#include "CameraSystem.hpp"
#include "CameraComponent.hpp"

namespace MeowEngine::Runtime {
    GameplaySystem::GameplaySystem() {
        MeowEngine::Log("GameplaySystem", "Constructed");

        ComponentSystems.push_back(std::make_unique<CameraSystem>());
    }

    GameplaySystem::~GameplaySystem() {
        MeowEngine::Log("GameplaySystem", "Destructed");
    }

    void GameplaySystem::SetWorld(Asset::World* world) {
        World = world;
    }

    Asset::World& GameplaySystem::GetWorld() {
        return *World;
    }

    void GameplaySystem::Input() {}

    void GameplaySystem::Update() {
        for (auto& system : ComponentSystems) {
            system->Update(*World);
        }
    }

    void GameplaySystem::SetViewport(const float& width, const float& height) {
        World->GetComponent<CameraComponent>(World->ActiveCamera).SetViewport(width, height);
    }

    CameraComponent& GameplaySystem::GetCamera() const {
        return World->GetComponent<CameraComponent>(World->ActiveCamera);
    }
}
