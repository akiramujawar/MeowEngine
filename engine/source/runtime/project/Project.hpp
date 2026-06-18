//
// Created by Akira Mujawar on 11/03/26.
//

#ifndef MEOWENGINETEST2_PROJECT_HPP
#define MEOWENGINETEST2_PROJECT_HPP

#include <ProjectSettings.hpp>
#include "ApplicationConfig.hpp"

namespace MeowEngine::Runtime {
    class Project {
    public:
        Project();
        ~Project();

        void Init();

        Settings::ProjectSettings Settings;
        Asset::ApplicationConfig Config;
    };
}


#endif //MEOWENGINETEST2_PROJECT_HPP