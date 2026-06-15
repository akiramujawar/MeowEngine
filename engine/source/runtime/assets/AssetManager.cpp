//
// Created by Akira Mujawar on 05/03/26.
//

#include "AssetManager.hpp"

#include "log.hpp"
#include "AssetManagerInitData.hpp"

// #include <AssetRegistrySerializer.hpp>
// #include <MeowService.hpp>
// #include <Project.hpp>

namespace MeowEngine::Asset {
    AssetManager::AssetManager() {
        MeowEngine::Log("AssetManager", "Constructed");
    }
    AssetManager::~AssetManager() {
        MeowEngine::Log("AssetManager", "Destructed");
    }

    void AssetManager::Init(const AssetManagerInitData& context) {
        MeowEngine::Log("AssetManager", "Init");

        // load asset registry
    }

    void AssetManager::Load() {
        Registry.Load();


    }

    void AssetManager::RebuidE() {
        Registry.RebuildE();
        // Directory.RebuildE();
    }
}
