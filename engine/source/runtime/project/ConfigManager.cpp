//
// Created by Akira Mujawar on 11/03/26.
//

#include "ConfigManager.hpp"


namespace MeowEngine::Runtime {
    ConfigManager::ConfigManager() : Paths(), SandboxConfig() {
        MeowEngine::Log("Project", "Constructed");
    }

    ConfigManager::~ConfigManager() {
        MeowEngine::Log("Project", "Destructed");
    }

    void ConfigManager::Setup() {
        Bootstrap();
        Load();
        Resolve();
    }

    void ConfigManager::Bootstrap() {
        Paths.Init();
        Paths.InitDevelopment();
    }

    void ConfigManager::Load() {
        // NOTE: ONLY in engine editor builds
        MeowEngine::Log("ConfigManager", Paths.GetSandboxRootPath().GetRawString());
        EditorConfig.LoadConfig(Paths.GetSandboxRootPath());
        SandboxConfig.LoadConfig(Paths.GetSandboxRootPath());

        // TODO: add a Standalone.yml for build runs (for standalone final builds)
    }

    void ConfigManager::Resolve() {
        // NOTE: ONLY in engine editor builds
        Paths.SetEngineRootPath(Path {EditorConfig.EngineRootPath});
    }
}
