//
// Created by Akira Mujawar on 06/07/22.
//

#ifndef VULKAN_ENGINE_ENGINE_HPP
#define VULKAN_ENGINE_ENGINE_HPP

#pragma once

#include <Project.hpp>
#include <AssetManager.hpp>

using namespace std;

namespace MeowEngine {
    struct Engine {
        Engine() {
            AppInstance = this;
        };

        virtual ~Engine() = default;

        virtual void CreateApplication() = 0;

        Runtime::Asset::AssetManager& GetAssetManager() {
            return AssetManager;
        }

        Runtime::Project& GetProject() {
            return Project;
        }

    private:
        inline static Engine* AppInstance;

        Runtime::Project Project;
        Runtime::Asset::AssetManager AssetManager;

    public:
        static Engine& Get() {
            return *AppInstance;
        }
    };
} // namespace MeowEngine


#endif //VULKAN_ENGINE_ENGINE_HPP
