//
// Created by Akira Mujawar on 05/03/26.
//

#include "AssetManager.hpp"

#include <log.hpp>

namespace MeowEngine::Runtime::Asset {
    AssetManager::AssetManager() : Resolver() {
        MeowEngine::Log("AssetManager", "Constructed");
        Resolver.Init();
    }
    AssetManager::~AssetManager() {
        MeowEngine::Log("AssetManager", "Destructed");
    }

    AssetResolver& AssetManager::GetResolver() {
        return Resolver;
    }
}