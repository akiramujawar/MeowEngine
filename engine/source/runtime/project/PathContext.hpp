//
// Created by Akira Mujawar on 26/02/26.
//

#ifndef MEOWENGINE_PATHCONTEXT_HPP
#define MEOWENGINE_PATHCONTEXT_HPP

#include <string>

#include <Public/IO/Include.hpp>

namespace MeowEngine::Settings {
    class PathContext {
    public:
        PathContext()
        : EngineRootPath("") // TODO: we retrieve this from Sandbox.txt
        , SandboxRootPath("")
        , ExecutablePath("")
        , EngineAssetRegistryPath("")
        , SandboxAssetRegistryPath("") {}

        void Init() {
            ExecutablePath = FileSystem::FileSystem::GetExecutablePath();
            MeowEngine::Log("Executable Path", ExecutablePath.GetRawString());

            auto engineAssetRegistry = ExecutablePath + "engine/assets/Registry";
            engineAssetRegistry.ReplaceExtension(".meowreg");
            EngineAssetRegistryPath = engineAssetRegistry;

            auto sandboxAssetRegistry = ExecutablePath + "assets/Registry";
            sandboxAssetRegistry.ReplaceExtension(".meowreg");
            SandboxAssetRegistryPath = sandboxAssetRegistry;
        }

        void InitDevelopment() {
            // we can get engine path by reading project metadata
            SandboxRootPath = ExecutablePath.GetParent().GetParent();
        }

        /**
         * NOTE: Only use inside editor code
         * @return
         */
        const Path& GetEngineRootPath() {
            return EngineRootPath;
        }

        /**
         * NOTE: Only use inside editor code
         * @return
         */
        const Path& GetSandboxRootPath() {
            return SandboxRootPath;
        }

        const Path& GetExecutablePath() {
            return ExecutablePath;
        }

        const Path& GetEngineAssetResolverPath() {
            return EngineAssetRegistryPath;
        }

        const Path& GetSandboxAssetResolverPath() {
            return SandboxAssetRegistryPath;
        }

        void SetEngineRootPath(const Path& path) {
            EngineRootPath = path;
        }

    private:
        // - for editor only
        // only use while running editor (@EngineRootPath & @SandboxRootPath)
        Path EngineRootPath;
        Path SandboxRootPath;

        // for runtime
        Path ExecutablePath;

        Path EngineAssetRegistryPath;
        Path SandboxAssetRegistryPath;
    };
}

#endif //MEOWENGINE_PATHCONTEXT_HPP

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