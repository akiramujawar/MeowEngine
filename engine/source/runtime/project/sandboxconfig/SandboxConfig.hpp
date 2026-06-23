//
// Created by Akira Mujawar on 17/06/26.
//

#ifndef MEOWENGINE_SANDBOXCONFIG_HPP
#define MEOWENGINE_SANDBOXCONFIG_HPP

#include "AssetHandle.hpp"

namespace MeowEngine::Asset {
    struct SandboxConfig {
        /**
         * Initial world to load with
         */
        AssetHandle LaunchWorldHandle;

        int WindowWidth;
        int WindowHeight;
    };
}

#endif //MEOWENGINE_SANDBOXCONFIG_HPP