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

#include <GraphicsDevice.hpp>
#include <Renderer.hpp>

#include <EditorModule.hpp>
#include <RuntimeModule.hpp>
#include <PhysicsModule.hpp>

#include <Project.hpp>
#include <AssetManager.hpp>
#include <InputManager.hpp>
#include <RenderSceneExtractor.hpp>


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
        void Close();

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

        /**
         * Returns stack instance of editor engine (which includes Selector, Reflection, Importer etc...)
         * @return
         */
        Editor::EditorModule& GetEditorModule() {
            return Editor;
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
        Graphics::GraphicsDevice GraphicsDevice;
        Rendering::Renderer Renderer;
        Rendering::RenderSceneExtractor RenderSceneExtractor;

        Editor::EditorModule Editor;
        Runtime::RuntimeModule Runtime;
        Physics::PhysicsModule Physics;


    };
} // namespace MeowEngine

// engine -> systems(scheduler) -> executor(scheduler)
// single thread executor -> execute jobs sequentially
// multi thread executor -> dispatch the jobs to job system for execution

// main thread
// gameplay thread
// render thread
// physics thread
// workers

#endif //MEOWENGINE_ENGINE_HPP
