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

    void GameplaySystem::SetWorld(Asset::World* world) {
        World = world;
    }

    Asset::World& GameplaySystem::GetWorld() {
        return *World;
    }

    void GameplaySystem::Input() {}

    void GameplaySystem::Update() {

    }
}
