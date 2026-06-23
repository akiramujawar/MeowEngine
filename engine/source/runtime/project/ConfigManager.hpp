//
// Created by Akira Mujawar on 11/03/26.
//

#ifndef MEOWENGINE_CONFIGMANAGER_HPP
#define MEOWENGINE_CONFIGMANAGER_HPP

#include "PathContext.hpp"
#include "SandboxConfig.hpp"
#include "EditorConfig.hpp"

namespace MeowEngine::Runtime {
    class ConfigManager {
    public:
        ConfigManager();
        ~ConfigManager();

        void Setup();

    private:
        void Bootstrap();
        void Load();
        void Resolve();

    public:
        Settings::PathContext Paths;

        Asset::SandboxConfig SandboxConfig;
        Asset::EditorConfig EditorConfig;

        // paths load
        // - deserialize EditorConfig
        // paths init
        // - setup
        // asset manager init
        // - setup asset registry
        // - setup asset cache
        // - setup asset directory
        // asset manager load
        // - load registry
        // - load directory
    };
}


#endif //MEOWENGINE_CONFIGMANAGER_HPP