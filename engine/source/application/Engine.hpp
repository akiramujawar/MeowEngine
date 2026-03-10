//
// Created by Akira Mujawar on 06/07/22.
//

#ifndef VULKAN_ENGINE_ENGINE_HPP
#define VULKAN_ENGINE_ENGINE_HPP

#pragma once

#include <AssetManager.hpp>

using namespace std;

namespace MeowEngine {
    struct Engine {
        Engine() = default;
        virtual ~Engine() = default;

        virtual void CreateApplication() {
            AppInstance = this;
        };

        static Engine& Get() {
            return *AppInstance;
        }

        Runtime::Asset::AssetManager& GetAssetManager() {
            return AssetManager;
        }

    private:
        inline static Engine* AppInstance;

        Runtime::Asset::AssetManager AssetManager;
    };
} // namespace MeowEngine


#endif //VULKAN_ENGINE_ENGINE_HPP
