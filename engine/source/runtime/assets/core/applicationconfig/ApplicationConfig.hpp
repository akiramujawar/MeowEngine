//
// Created by Akira Mujawar on 17/06/26.
//

#ifndef MEOWENGINE_APPLICATIONCONFIG_HPP
#define MEOWENGINE_APPLICATIONCONFIG_HPP

#include "AssetHandle.hpp"

namespace MeowEngine::Asset {
    struct ApplicationConfig {
        /**
         * Initial world to load with
         */
        AssetHandle LaunchWorldHandle;

        int WindowWidth;
        int WindowHeight;
    };
}

#endif //MEOWENGINE_APPLICATIONCONFIG_HPP