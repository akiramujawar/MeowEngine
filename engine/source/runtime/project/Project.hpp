//
// Created by Akira Mujawar on 11/03/26.
//

#ifndef MEOWENGINETEST2_PROJECT_HPP
#define MEOWENGINETEST2_PROJECT_HPP

#include <ProjectSettings.hpp>

namespace MeowEngine::Runtime {
    class Project {
    public:
        Project();
        ~Project();

        void Init();

        Settings::ProjectSettings Settings;
    };
}


#endif //MEOWENGINETEST2_PROJECT_HPP