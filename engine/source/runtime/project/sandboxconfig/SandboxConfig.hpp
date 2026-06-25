//
// Created by Akira Mujawar on 17/06/26.
//

#ifndef MEOWENGINE_SANDBOXCONFIG_HPP
#define MEOWENGINE_SANDBOXCONFIG_HPP

#include <string>

#include "Public/Core/Forward.hpp"
#include "AssetHandle.hpp"


namespace MeowEngine::Runtime {
    struct SandboxConfig {
        /**
         * Initial world to load with
         */
        Asset::AssetHandle LaunchWorldHandle;

        void LoadConfig(const Path& path);

        int WindowWidth;
        int WindowHeight;
    };
}

#endif //MEOWENGINE_SANDBOXCONFIG_HPP