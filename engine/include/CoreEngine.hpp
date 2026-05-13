//
// Created by Akira Mujawar on 13/05/26.
//

#ifndef MEOWENGINE_APPLICATION_HPP
#define MEOWENGINE_APPLICATION_HPP

#include <Engine.hpp>
#include <AssetManager.hpp>
#include <Project.hpp>

namespace MeowEngine {
    inline Runtime::Asset::AssetManager& GetAssetManager() {
        return Engine::Get().GetAssetManager();
    }

    inline Runtime::Project& GetProject() {
        return Engine::Get().GetProject();
    }
}

#endif //MEOWENGINE_APPLICATION_HPP