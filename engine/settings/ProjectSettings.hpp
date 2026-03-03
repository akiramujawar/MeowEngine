//
// Created by Akira Mujawar on 26/02/26.
//

#ifndef MEOWENGINE_PROJECTSETTINGS_HPP
#define MEOWENGINE_PROJECTSETTINGS_HPP

#include "string"

namespace MeowEngine::Settings {
    class ProjectSettings {
    public:
        static void SetProjectPath(const std::string& path) {
            ProjectPath = path;
        }

        static const std::string& GetEnginePath() {
            return ProjectSettings::EnginePath;
        }

        static const std::string& GetProjectPath() {
            return ProjectSettings::ProjectPath;
        }

    private:
        inline static std::string EnginePath = "";
        inline static std::string ProjectPath = "project";
    };
}

#endif //MEOWENGINE_PROJECTSETTINGS_HPP

// console - static path?
// panel to open project. we feed that path open project?
// how can i have engine build separate & project build separate

// when loading engine
// separate engine build & separate project build

// currently
// setups using .sh
// then builds and run using .cmake

// ideally
// on console
// setup using cmake
// build selected project & engine using cmake & run

// on mac/win
// setup using cmake
// build dll or something similar using cmake
// build project along with the dll and run

// on web (its different)