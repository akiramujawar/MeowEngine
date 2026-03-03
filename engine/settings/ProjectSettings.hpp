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
