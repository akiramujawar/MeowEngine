//
// Created by Akira Mujawar on 25/06/26.
//

#include "SandboxConfig.hpp"

#include <fstream>

#include "Public/Core/Include.hpp"

namespace MeowEngine::Runtime {
    void SandboxConfig::LoadConfig(const Path& path) {
        const auto sandboxConfigPath = path + "Sandbox.yml";
        ConfigPath = sandboxConfigPath.GetRawString();
        Config = YAML::LoadFile(sandboxConfigPath.GetRawString());

        LaunchWorldGuid = Config["LaunchWorldGuid"].as<uint64_t>();
    }

    void SandboxConfig::SaveConfig() const {
        // Modify
        // Config["WorldLaunchGUID"] = LaunchWorldGuid;

        // Write back
        YAML::Emitter out;
        out << Config;

        std::ofstream file(ConfigPath);
        file << out.c_str();
    }
}
