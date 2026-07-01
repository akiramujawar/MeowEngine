//
// Created by Akira Mujawar on 17/06/26.
//

#ifndef MEOWENGINE_SANDBOXCONFIG_HPP
#define MEOWENGINE_SANDBOXCONFIG_HPP

#include <string>
#include <cstdlib>

#include "YamlCppAPI.hpp"
#include "Public/Core/Forward.hpp"

namespace MeowEngine::Runtime {
    struct SandboxConfig {
        /**
         * Initial world to load with
         */
        uint64_t LaunchWorldGuid;

        int WindowWidth;
        int WindowHeight;

        void LoadConfig(const Path& path);
        void SaveConfig() const;
        YAML::Node& GetConfig() { return Config;}

    private:
        YAML::Node Config;
        std::string ConfigPath;
    };
}

#endif //MEOWENGINE_SANDBOXCONFIG_HPP