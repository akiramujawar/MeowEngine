//
// Created by Akira Mujawar on 05/03/26.
//

#include "AssetManager.hpp"

#include <log.hpp>
#include <AssetRegistrySerializer.hpp>
#include <Core.hpp>


namespace MeowEngine::Runtime::Asset {
    AssetManager::AssetManager() : Resolver() {
        MeowEngine::Log("AssetManager", "Constructed");
    }
    AssetManager::~AssetManager() {
        MeowEngine::Log("AssetManager", "Destructed");
    }

    void AssetManager::Init() {
        MeowEngine::Log("AssetManager", "Init");

        Serializer::AssetRegistrySerializer::Deserialize(
            GetProject().ProjectSettings.GetAssetResolverPath(),
            Resolver
        );
    }

    AssetRegistry& AssetManager::GetResolver() {
        return Resolver;
    }
}