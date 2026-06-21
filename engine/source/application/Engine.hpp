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

#include <InputDevice.hpp>
#include <GraphicsDevice.hpp>

#include <Renderer.hpp>
#include <RenderExtractor.hpp>

#include <EditorModule.hpp>
#include <RuntimeModule.hpp>
#include <PhysicsModule.hpp>

#include <Project.hpp>
#include <AssetManager.hpp>


using namespace std;

namespace MeowEngine {
    /**
     * TODO: Implemented PIMPL pattern
     */
    struct Engine {
    public:
        Engine();
        virtual ~Engine();

        /**
         * TODO: remove
         */
        virtual void CreateApplication() {};
        void Open();
        void Close();

#if __WEB__
        void WebLoop() {
            Schedule();
        }
#endif

    private:
        /**
         * Initialise engine systems
         */
        void Init();

        /**
         * Load project and other engine specific assets
         */
        void Load();

        /**
         * Main loop for scheduling processes
         */
        void Loop();

        /**
         *
         */
        void Schedule();

        /**
         * Unload any engine specific assets
         */
        void Unload();

        /**
         * Close all threads and processes
         */
        void Shutdown();

        bool ProcessDeviceInput(const Input::InputEvents& events);

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
        Asset::AssetManager AssetManager;
        Input::InputDevice InputDevice;
        Core::Timing Timing;

        // messaging
        Messaging::CommandQueue CommandQueue;
        Messaging::EventBus EventBus;
        Messaging::RequestQueue RequestQueue;

        // modules
        Graphics::GraphicsDevice GraphicsDevice;
        Rendering::Renderer Renderer;
        Rendering::RenderExtractor RenderExtractor;
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

// physics result inside physics - takes physics snapshot to apply data
// runtime contains physics snapshot & render snapshot - takes physics results to apply data

// dedicated shader folder for raw code files
// dedicated assets folder
// dedicated cpp/hpp folder
//  - on engine run
//      - check for shader if (duplicates throw error)
//      - combine shader into .meowasset and save in .compiled/shader folder (folder will be hidden)
//      - for now the only optimsation would be if compiled asset exists we only override the shader code
//  - we will use these files as our shader asset
//  - inside filesystem ui, we show the compiled shaders & not the raw shaders
//  - drag n drop to reference this asset

// input module - owned by engine.hpp
// - input manager
// - input double buffer
// - input double buffer swap at sync point along with render scene extractor & physics extractor

// engine needs to process input differently - like close, open, user events (will replace with commands / requests in future)
// scene needs to use input differently - move, look around, trigger scene events
// ui needs to use input differetntly - drag n drop, imgui, button click, open tracy client etc...


// ShaderAssetImporter
// ShaderAsset
// ShaderSerializer
// -- AssetRegistry::GetPath(assethandle)
// -- ShaderAssetImporter::Load(path)
// -- ShaderAsset

#endif //MEOWENGINE_ENGINE_HPP
