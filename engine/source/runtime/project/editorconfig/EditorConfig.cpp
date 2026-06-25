//
// Created by Akira Mujawar on 23/06/26.
//

#include "EditorConfig.hpp"
#include "YamlCppAPI.hpp"

#include "Public/Core/Include.hpp"

namespace MeowEngine::Runtime {
    void EditorConfig::Load(const Path& path) {
        const auto editorConfigPath = path + "Editor.yml";
        YAML::Node config = YAML::LoadFile(editorConfigPath.GetRawString());

        EngineRootPath = config["ENGINE_PATH"].as<std::string>();
    }
}
