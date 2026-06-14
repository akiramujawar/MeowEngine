//
// Created by Akira Mujawar on 11/03/26.
//

#include "Project.hpp"

namespace MeowEngine::Runtime {
    Project::Project() : Settings() {
        MeowEngine::Log("Project", "Constructed");
    }

    Project::~Project() {
        MeowEngine::Log("Project", "Destructed");
    }

    void Project::Init() {
        Settings.Init();
    }
}
