//
// Created by Akira Mujawar on 26/02/26.
//

#ifndef MEOWENGINE_PROJECTSETTINGS_HPP
#define MEOWENGINE_PROJECTSETTINGS_HPP

#include <string>
#include <IO.hpp>

namespace MeowEngine::Settings {
    class ProjectSettings {
    public:
        ProjectSettings()
        : EnginePath("")
        , ProjectPath("")
        , ProjectMetadataPath("")
        , AssetRegistryPath("") {}

        void SetProjectPath(const std::string& path) {
            const auto projectPath = FileSystem::Path(path);
            auto meowProject = projectPath + projectPath.GetName();
            meowProject.ReplaceExtension(".meowproject");

            auto assetRegistry = projectPath + "Registry";
            assetRegistry.ReplaceExtension(".meowdata");

            ProjectPath = FileSystem::Path(path);
            ProjectMetadataPath = meowProject;
            AssetRegistryPath = assetRegistry;
        }

        const FileSystem::Path& GetEnginePath() {
            return EnginePath;
        }

        const FileSystem::Path& GetProjectPath() {
            return ProjectPath;
        }

        const FileSystem::Path& GetAssetResolverPath() {
            return AssetRegistryPath;
        }

    private:
        FileSystem::Path EnginePath;
        FileSystem::Path ProjectPath;
        FileSystem::Path ProjectMetadataPath;
        FileSystem::Path AssetRegistryPath;
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