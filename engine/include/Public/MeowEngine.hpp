//
// Created by Akira Mujawar on 14/05/26.
//

#ifndef MEOWENGINE_MEOWENGINE_HPP
#define MEOWENGINE_MEOWENGINE_HPP

// #include <Engine.hpp>
#include <AssetManager.hpp>
#include <Project.hpp>

namespace MeowEngine::Runtime {
    class Project;
    namespace Asset { class AssetManager; }

    Asset::AssetManager& GetAssetManager();
    Project& GetProject();
}


#endif //MEOWENGINE_MEOWENGINE_HPP