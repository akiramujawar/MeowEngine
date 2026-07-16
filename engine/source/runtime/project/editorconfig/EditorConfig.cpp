//
// Created by Akira Mujawar on 23/06/26.
//


#include "EditorConfig.hpp"

#include <fstream>

#include "YamlCppAPI.hpp"
#include "Public/Core/Include.hpp"

namespace MeowEngine::Runtime {
    void EditorConfig::LoadConfig(const Path& path) {
        const auto editorConfigPath = path + "Editor.yml";
        ConfigPath = editorConfigPath.GetRawString();
        Config = YAML::LoadFile(editorConfigPath.GetRawString());

        EngineRootPath = Config["ENGINE_PATH"].as<std::string>();

        ProjectIconGuid = Config["ProjectIconGuid"].as<uint64_t>();
        FolderIconGuid = Config["FolderIconGuid"].as<uint64_t>();
        HppIconGuid = Config["HppIconGuid"].as<uint64_t>();
        CppIconGuid = Config["CppIconGuid"].as<uint64_t>();
        ShaderIconGuid = Config["ShaderIconGuid"].as<uint64_t>();
        MeshIconGuid = Config["MeshIconGuid"].as<uint64_t>();
        TextureIconGuid = Config["TextureIconGuid"].as<uint64_t>();
        WorldIconGuid = Config["WorldIconGuid"].as<uint64_t>();
        UnknownIconGuid = Config["UnknownIconGuid"].as<uint64_t>();

        PlayButtonIconGuid = Config["PlayButtonIconGuid"].as<uint64_t>();
        StopButtonIconGuid = Config["StopButtonIconGuid"].as<uint64_t>();
        PauseButtonIconGuid = Config["PauseButtonIconGuid"].as<uint64_t>();
        UnPauseButtonIconGuid = Config["UnPauseButtonIconGuid"].as<uint64_t>();
    }

    void EditorConfig::SaveConfig() const {
        // Write back
        YAML::Emitter out;
        out << Config;

        std::ofstream file(ConfigPath);
        file << out.c_str();
    }
}
