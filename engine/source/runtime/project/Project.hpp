//
// Created by Akira Mujawar on 11/03/26.
//

#ifndef MEOWENGINETEST2_PROJECT_HPP
#define MEOWENGINETEST2_PROJECT_HPP

#include <ProjectSettings.hpp>
#include <AssetRegistry.hpp>

namespace MeowEngine::Runtime {
    class Project {
    public:
        Project() : ProjectSettings() {} ;

        Settings::ProjectSettings ProjectSettings;
        Asset::AssetRegistry AssetResolver;
    };
}


#endif //MEOWENGINETEST2_PROJECT_HPP