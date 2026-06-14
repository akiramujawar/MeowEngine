//
// Created by Akira Mujawar on 26/02/26.
//

#ifndef MEOWENGINE_PROJECTSETTINGS_HPP
#define MEOWENGINE_PROJECTSETTINGS_HPP

#include <string>
#include <Public/IO.hpp>

namespace MeowEngine::Settings {
    class ProjectSettings {
    public:
        ProjectSettings()
        : EnginePath("") // TODO: we retrieve this from Sandbox.txt
        , ProjectPath("")
        , ExecutablePath("")
        , ProjectMetadataPath("")
        , AssetRegistryPath("") {}

        void Init() {
            ExecutablePath = FileSystem::FileSystem::GetExecutablePath();
            MeowEngine::Log("Executable Path", ExecutablePath.GetRawString());

            auto assetRegistry = ExecutablePath + "Registry";
            assetRegistry.ReplaceExtension(".meowdata");

            AssetRegistryPath = assetRegistry;
        }

        void InitDevelopment() {
            ProjectPath = ExecutablePath.GetParent().GetParent();

            auto meowProject = ProjectPath + ProjectPath.GetName();
            meowProject.ReplaceExtension(".meowproject");
            ProjectMetadataPath = meowProject;
        }

        /**
         * NOTE: Only use inside editor code
         * @return
         */
        const FileSystem::Path& GetEnginePath() {
            return EnginePath;
        }

        /**
         * NOTE: Only use inside editor code
         * @return
         */
        const FileSystem::Path& GetProjectPath() {
            return ProjectPath;
        }

        const FileSystem::Path& GetExecutablePath() {
            return ExecutablePath;
        }

        const FileSystem::Path& GetAssetResolverPath() {
            return AssetRegistryPath;
        }

    private:
        FileSystem::Path EnginePath;
        FileSystem::Path ProjectPath;
        FileSystem::Path ExecutablePath;
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