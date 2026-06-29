//
// Created by Akira Mujawar on 15/05/26.
//

#include <log.hpp>
#include <WorldManager.hpp>

#include "MeowService.hpp"
#include "CommandQueue.hpp"
#include "RequestQueue.hpp"
#include "AssetManager.hpp"
#include "GameplaySystem.hpp"

#include "World.hpp"
#include "DefaultWorld.hpp"
#include "AssetHandleWorld.hpp"
#include "HierarchyWorld.hpp"
#include "ReflectionWorld.hpp"

#include "SaveTempWorldRequest.hpp"

namespace MeowEngine::Runtime {
    WorldManager::WorldManager() {
        MeowEngine::Log("WorldManager", "Constructed");
    }
    WorldManager::~WorldManager() {
        MeowEngine::Log("WorldManager", "Destructed");
    }

    void WorldManager::Init(GameplaySystem* gameplay) {
        Gameplay = gameplay;
    }

    void WorldManager::Load(const Asset::AssetHandle& handle, bool isResetCamera) {
        auto& assetManager = MeowService().AssetManager;

        if (auto* world = assetManager.GetAssetOrLoad<Asset::World>(handle)) {
            // tempWorld
            Gameplay->SetWorld(world);
            ActiveWorldHandle = handle;
        }
        else {
            const auto tempHandle = assetManager.CreateTempAsset<DefaultWorld>();
            auto* tempWorld = assetManager.GetAsset<DefaultWorld>(tempHandle);
            Gameplay->SetWorld(tempWorld);
            ActiveWorldHandle = tempHandle;
        }

        if (isResetCamera) {
            Gameplay->ResetCamera();
        }
    }

    // void WorldManager::LoadAsync(const Asset::AssetHandle& world, std::function<void()> callback) {}
    // void WorldManager::Unload(const Asset::AssetHandle& world) {}
    // void WorldManager::UnloadAsync(const Asset::AssetHandle& world, std::function<void()> callback) {}
    // void WorldManager::Reload(const Asset::AssetHandle& world) {}
    // void WorldManager::ReloadAsync(const Asset::AssetHandle& world, std::function<void()> callback) {}
    // void WorldManager::Switch(const Asset::AssetHandle& world) {}
    // void WorldManager::Add(const Asset::AssetHandle& world) {}

    void WorldManager::Save() {
        if (ActiveWorldHandle.GetIsTemp()) {
            MeowService().RequestQueue.Push(
                Messaging::ThreadType::MAIN,
                Messaging::ThreadType::MAIN,
                std::make_unique<Messaging::SaveTempWorldRequest>(ActiveWorldHandle)
            );
        }
        else {
            auto& assetManager = MeowService().AssetManager;
            assetManager.SaveAsset<Asset::World>(ActiveWorldHandle);
        }
    }

}
