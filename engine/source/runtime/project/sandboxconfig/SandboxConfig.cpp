//
// Created by Akira Mujawar on 25/06/26.
//

#include "SandboxConfig.hpp"

#include "YamlCppAPI.hpp"
#include "Public/Core/Include.hpp"

namespace MeowEngine::Runtime {
    void SandboxConfig::LoadConfig(const Path& path) {
        const auto sandboxConfigPath = path + "Sandbox.yml";
        YAML::Node config = YAML::LoadFile(sandboxConfigPath.GetRawString());

        // EngineRootPath = config["ENGINE_PATH"].as<std::string>();
    }
}
