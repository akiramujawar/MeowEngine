//
// Created by Akira Mujawar on 06/07/22.
//

#ifndef MEOWENGINE_ENGINE_ENGINE_HPP
#define MEOWENGINE_ENGINE_ENGINE_HPP

#pragma once

#include <Threading.hpp>

#include <Scheduler.hpp>
#include <RenderGraph.hpp>
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
#include <InputManager.hpp>

#include <EditorUISystem.hpp>

using namespace std;

namespace MeowEngine {
    /**
     * TODO: Implemented PIMPL pattern
     */
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
        void Open();

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
        void Run();
        void ShutDown();

        bool ProcessDeviceInput();

    private:
        // TODO: needs to be atomic
        bool IsRunning;

        // logic & threading
        Threading::JobSystem JobSystem;
        Shared::Scheduler Scheduler;
        Shared::RenderGraph RenderGraph;

        Core::Timing Timing;

        // execution logic for single/multi thread
        std::unique_ptr<Application::IExecutor> Executor;

        // essentials
        Runtime::Project Project;
        Runtime::Asset::AssetManager AssetManager;
        Runtime::InputManager InputManager;

        // messaging
        Runtime::Messaging::CommandQueue CommandQueue;
        Runtime::Messaging::EventBus EventBus;
        Runtime::Messaging::RequestQueue RequestQueue;

        // systems
        Runtime::Systems::MainSystem MainSystem;
        Runtime::Systems::PhysicsSystem PhysicsSystem;
        Runtime::Systems::RenderSystem RenderSystem;

        Editor::Systems::EditorUISystem EditorUI;
    };
} // namespace MeowEngine


#endif //MEOWENGINE_ENGINE_ENGINE_HPP
