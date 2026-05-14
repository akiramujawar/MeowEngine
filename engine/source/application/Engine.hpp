//
// Created by Akira Mujawar on 06/07/22.
//

#ifndef MEOWENGINE_ENGINE_HPP
#define MEOWENGINE_ENGINE_HPP

#pragma once

#include <Public/Threading/Forward.hpp>
#include <Timing.hpp>

#include <IExecutor.hpp>

#include <CommandQueue.hpp>
#include <EventBus.hpp>
#include <RequestQueue.hpp>

#include <EditorModule.hpp>

#include <GraphicsDevice.hpp>

#include <MainSystem.hpp>
#include <PhysicsSystem.hpp>
#include <RenderSystem.hpp>

#include <Project.hpp>
#include <AssetManager.hpp>
#include <InputManager.hpp>


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

        Editor::EditorModule& GetEditorModule() {
            return EditorModule;
        }


    private:
        void Init();
        void Loop();
        void ShutDown();

        bool ProcessDeviceInput();

    private:
        // TODO: needs to be atomic
        bool IsRunning;

        // threading
        Threading::JobSystem JobSystem;
        Threading::Scheduler Scheduler;

        // execution logic for single/multi thread
        std::unique_ptr<Application::IExecutor> Executor;

        // essentials
        Runtime::Project Project;
        Runtime::Asset::AssetManager AssetManager;
        Runtime::InputManager InputManager;
        Core::Timing Timing;

        // messaging
        Runtime::Messaging::CommandQueue CommandQueue;
        Runtime::Messaging::EventBus EventBus;
        Runtime::Messaging::RequestQueue RequestQueue;

        // modules
        Editor::EditorModule EditorModule;

        // graphics
        Graphics::GraphicsDevice GraphicsDevice;

        // systems
        Runtime::Systems::MainSystem MainSystem;
        Runtime::Systems::PhysicsSystem PhysicsSystem;
        Rendering::RenderSystem RenderSystem;
    };
} // namespace MeowEngine

// engine -> systems(scheduler) -> executor(scheduler)
// single thread executor -> execute jobs sequentially
// multi thread executor -> dispatch the jobs to job system for execution

#endif //MEOWENGINE_ENGINE_HPP
