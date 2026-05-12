//
// Created by Akira Mujawar on 11/03/26.
//

#include "Project.hpp"

namespace MeowEngine::Runtime {
    Project::Project() : ProjectSettings() {
        MeowEngine::Log("Project", "Constructed");
    }

    Project::~Project() {
        MeowEngine::Log("Project", "Destructed");
    }
}