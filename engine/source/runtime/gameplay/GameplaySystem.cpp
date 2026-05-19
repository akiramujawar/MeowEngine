//
// Created by Akira Mujawar on 17/04/26.
//

#include <GameplaySystem.hpp>
#include <log.hpp>

namespace MeowEngine::Runtime {
    GameplaySystem::GameplaySystem() {
        MeowEngine::Log("GameplaySystem", "Constructed");
    }

    GameplaySystem::~GameplaySystem() {
        MeowEngine::Log("GameplaySystem", "Destructed");
    }

    void GameplaySystem::SetWorld(Runtime::World* world) {
        World = world;
    }

    World& GameplaySystem::GetWorld() {
        return *World;
    }

    void GameplaySystem::Input() {}

    void GameplaySystem::Update() {

    }
}
