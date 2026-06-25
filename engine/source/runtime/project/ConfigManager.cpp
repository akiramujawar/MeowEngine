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
        EditorConfig.Load(Paths.GetSandboxRootPath());
    }

    void ConfigManager::Resolve() {
        // NOTE: ONLY in engine editor builds
        Paths.SetEngineRootPath(Path {EditorConfig.EngineRootPath});
    }
}
