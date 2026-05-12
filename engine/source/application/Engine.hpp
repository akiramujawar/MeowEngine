//
// Created by Akira Mujawar on 06/07/22.
//

#ifndef MEOWENGINE_ENGINE_ENGINE_HPP
#define MEOWENGINE_ENGINE_ENGINE_HPP

#pragma once

#include <Threading.hpp>
#include <Timing.hpp>

#include <IExecutor.hpp>

#include <CommandQueue.hpp>
#include <EventBus.hpp>
#include <RequestQueue.hpp>

#include <MainSystem.hpp>
#include <RenderSystem.hpp>
#include <PhysicsSystem.hpp>

#include <Project.hpp>
#include <AssetManager.hpp>

using namespace std;

namespace MeowEngine {
    struct Engine {
    public:
        static Engine& Get() {
            return *AppInstance;
        }

    private:
        inline static Engine* AppInstance;

    public:
        Engine();
        virtual ~Engine();

        /**
         * TODO: remove
         */
        virtual void CreateApplication() {};

        void Run();

        /**
         * Returns stack instance of asset manager
         * @return
         */
        Runtime::Asset::AssetManager& GetAssetManager() {
            return AssetManager;
        }

        /**
         * Returns stack instance of project (which includes asset registry, settings)
         * @return
         */
        Runtime::Project& GetProject() {
            return Project;
        }

    private:
        //
        bool IsRunning;

        // threading
        Threading::Scheduler Scheduler;
        Threading::JobSystem JobSystem;
        Core::Timing Timing;

        // execution logic for single/multi thread
        std::unique_ptr<Application::IExecutor> Executor;

        // essentials
        Runtime::Project Project;
        Runtime::Asset::AssetManager AssetManager;

        // messaging
        Runtime::Messaging::CommandQueue CommandQueue;
        Runtime::Messaging::EventBus EventBus;
        Runtime::Messaging::RequestQueue RequestQueue;

        // systems
        Runtime::Systems::MainSystem MainSystem;
        Runtime::Systems::PhysicsSystem PhysicsSystem;
        Runtime::Systems::RenderSystem RenderSystem;
    };
} // namespace MeowEngine


#endif //MEOWENGINE_ENGINE_ENGINE_HPP
