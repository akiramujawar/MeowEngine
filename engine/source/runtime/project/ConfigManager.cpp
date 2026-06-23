//
// Created by Akira Mujawar on 11/03/26.
//

#include "ConfigManager.hpp"

namespace MeowEngine::Runtime {
    ConfigManager::ConfigManager() : Paths() {
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
        // TODO: load configs
    }

    void ConfigManager::Resolve() {
        // TODO: use config to update engine path
    }
}
