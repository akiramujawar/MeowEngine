//
// Created by Akira Mujawar on 15/05/26.
//

#include <log.hpp>
#include <WorldManager.hpp>

#include "GameplaySystem.hpp"

namespace MeowEngine::Runtime {
    WorldManager::WorldManager() {
        MeowEngine::Log("WorldManager", "Constructed");
    }
    WorldManager::~WorldManager() {
        MeowEngine::Log("WorldManager", "Destructed");
    }

    void WorldManager::Setup(WorldManager* manager, GameplaySystem* gameplay) {
        Instance = manager;
        Instance->Gameplay = gameplay;
    }

    void WorldManager::Load(const Asset::AssetHandle& world) {
        // Instance.Gameplay->SetWorld();
    }

    void WorldManager::LoadAsync(const Asset::AssetHandle& world, std::function<void()> callback) {}
    void WorldManager::Unload(const Asset::AssetHandle& world) {}
    void WorldManager::UnloadAsync(const Asset::AssetHandle& world, std::function<void()> callback) {}
    void WorldManager::Reload(const Asset::AssetHandle& world) {}
    void WorldManager::ReloadAsync(const Asset::AssetHandle& world, std::function<void()> callback) {}
    void WorldManager::Switch(const Asset::AssetHandle& world) {}
    void WorldManager::Add(const Asset::AssetHandle& world) {}
    void WorldManager::Save(const Asset::AssetHandle& world) {}

    WorldManager* WorldManager::Instance = nullptr;
}
