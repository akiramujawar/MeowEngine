//
// Created by Akira Mujawar on 14/05/26.
//

#include <Public/MeowEngine.hpp>

#include <Engine.hpp>
// #include <AssetManager.hpp>
// #include <Project.hpp>

namespace MeowEngine::Runtime {
    Asset::AssetManager& GetAssetManager() {
        return Engine::Get().GetAssetManager();
    }

    Project& GetProject() {
        return Engine::Get().GetProject();
    }

}
