//
// Created by Akira Mujawar on 23/06/26.
//

#ifndef MEOWENGINE_EDITORCONFIG_HPP
#define MEOWENGINE_EDITORCONFIG_HPP

#include <cstdlib>
#include <string>

#include "YamlCppAPI.hpp"
#include "Public/Core/Forward.hpp"

namespace MeowEngine::Runtime {
    struct EditorConfig {
        std::string EngineRootPath;

        uint64_t ProjectIconGuid;
        uint64_t FolderIconGuid;
        uint64_t HppIconGuid;
        uint64_t CppIconGuid;
        uint64_t ShaderIconGuid;
        uint64_t MeshIconGuid;
        uint64_t TextureIconGuid;
        uint64_t WorldIconGuid;
        uint64_t UnknownIconGuid;

        // engine root path
        // handles for asset thumbnails
        void LoadConfig(const Path& path);
        void SaveConfig() const;
        YAML::Node& GetConfig() { return Config;}

    private:
        YAML::Node Config;
        std::string ConfigPath;
    };
}


#endif //MEOWENGINE_EDITORCONFIG_HPP