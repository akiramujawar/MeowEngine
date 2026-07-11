//
// Created by Akira Mujawar on 06/07/22.
//

#include <Engine.hpp>

#include <AppIcon.hpp>
#include <MeowService.hpp>

#include <MultiThreadExecutor.hpp>
#include <SingleThreadExecutor.hpp>

#include <UserDeviceInputType.hpp>
#include <RenderCommand.hpp>

#include <MeowServiceInitData.hpp>
#include "InputDeviceInit.hpp"
#include <RendererInitData.hpp>
#include <RenderExtractorInitData.hpp>
#include "AssetManagerInitData.hpp"
#include "RuntimeInitData.hpp"
#include <EditorInitData.hpp>
#include <MessageInitData.hpp>
#include "EventContainer.hpp"
#include "GameplayStateContext.hpp"

#include "SaveProjectCommand.hpp"

#if __WEB__
#include <EmscriptenAPI.hpp>

namespace {
    void EmscriptenLoop(MeowEngine::Engine* engine) {
        MeowEngine::Log("Emscripten", "Looping");
        engine->WebLoop();
    }
}
#endif

namespace MeowEngine {
    Engine::Engine()
        : IsRunning(false)
    {
        SetAppIcon();
        MeowEngine::Log("Engine", "Initializing Engine...");

        try {
#ifdef __MULTI_THREAD__
            MeowEngine::Log("Engine", "Creating MultiThread Engine...");
            Executor = std::make_unique<Application::MultiThreadExecutor>(JobSystem);
#else
            MeowEngine::Log("Engine", "Creating SingleThread Engine...");
            Executor = std::make_unique<Application::SingleThreadExecutor>();
#endif
        }
        catch (std::exception& exception) {
            MeowEngine::Log("Engine", "Application failed to initialized", exception);
        }
    }

    Engine::~Engine() {
        MeowEngine::Log("Engine", "Closing Engine...");
        Executor.reset();
    }

    void Engine::Open() {
        IsRunning = true;

        ConfigManager.Setup();

        Init();
        SubscribeToEvents();
        Build();
        Load();

#if __WEB__
        emscripten_set_main_loop_arg((em_arg_callback_func) ::EmscriptenLoop, this, 60, 1);
#else
        Loop();
#endif
    }

    void Engine::Close() {
        IsRunning = false;

        Unload();
        Shutdown();
    }

    void Engine::Init() {
        PT_PROFILE_SCOPE;

        Rendering::RenderCommand::Init(Rendering::GraphicsType::OPENGL);

        Input::InputDeviceInitData inputDeviceInit{
            EventBus
        };

        InputDevice.Init(inputDeviceInit);

        Asset::AssetManagerInitData assetManagerInit{};
        AssetManager.Init(assetManagerInit);

        // -- runtime
        Runtime::RuntimeInitData runtimeInit{};
        Runtime.Init(runtimeInit);

        Physics::PhysicsInitData physicsInit{};
        Physics.Init(physicsInit);

        // -- editor
        Editor::EditorInitData editorInit {};
        editorInit.GraphicsDevice = &GraphicsDevice;
        editorInit.Project = &ConfigManager;

        Editor.Init(editorInit);

        // -- extraction
        Rendering::RenderExtractorInitData extractorInit {};
        extractorInit.Gameplay = &Runtime.GetGameplay();
        extractorInit.Selector = &Editor.GetSelector();
        extractorInit.AssetManager = &AssetManager;

        RenderExtractor.Init(extractorInit);

        // -- rendering
        // TODO: renderer.load so that imgui can load layout (currently inside init)
        Rendering::RendererInitData renderInit {};
        renderInit.Project = &ConfigManager;
        renderInit.GraphicsDevice = &GraphicsDevice;
        renderInit.InputDevice = &InputDevice;
        renderInit.Gameplay = &Runtime.GetGameplay();
        renderInit.CommandQueue = &CommandQueue;
        renderInit.RenderExtractor = &RenderExtractor;

        Renderer.Init(renderInit);

        // -- messaging
        Messaging::MessageInitData messageInit {};
        messageInit.Device = &GraphicsDevice;
        messageInit.Selector = &Editor.GetSelector();
        messageInit.FileDialog = &Editor.GetFileDialog();
        messageInit.AssetManager = &AssetManager;
        messageInit.WorldManager = &Runtime.GetWorldManager();
        messageInit.Gameplay = &Runtime.GetGameplay();
        messageInit.GameplayStateManager = &GameplayStateManager;
        messageInit.Physics = &Physics.GetPhysics();

        CommandQueue.Init(messageInit);
        RequestQueue.Init(messageInit);

        Runtime::GameplayStateContext gameplayStateContext{
            &Runtime.GetWorldManager(),
            &Runtime.GetGameplay(),
            &CommandQueue,
        };

        GameplayStateManager.Init(gameplayStateContext);

        MeowServiceInitData meowServiceInit {
            Timing,
            InputDevice.GetInputManager(),
            AssetManager,
            ConfigManager,
            Runtime.GetWorldManager(),
            EventBus,
            CommandQueue,
            RequestQueue,
            Editor
        };

        MeowService::Init(meowServiceInit);
    }

    void Engine::SubscribeToEvents() {
        MeowService().EventBus.Subscribe<Messaging::SceneViewportResizeEvent>(
           [&](const Messaging::SceneViewportResizeEvent& event) {
               // Runtime.GetGameplay().SetViewport(size.Width, size.Height);
               Rendering::RenderCommand::SetViewportSize(event.Width, event.Height);
           }
       );

        InputDevice.SubscribeToEvents();
        Runtime.SubscribeToEvents();
        Renderer.SubscribeToEvents();
    }

    void Engine::Build() {
        // any cache generation
        // in current case our shaders
        AssetBuilder.Build();
        AssetManager.RebuildDatabase();
    }

    void Engine::Load() {
        // asset registry load
        // load default scene if set
        // otherwise create new scene
        AssetManager.LoadAndBuild();
        Runtime.Load();
    }

    void Engine::Loop() {
        // ReSharper disable once CppDFAConstantConditions
        // ReSharper disable once CppDFAEndlessLoop
        while (IsRunning) {
            Schedule();
        }
    }

    void Engine::Schedule() {
        Scheduler.Clear();

        // -- runs on main thread
        Timing.Schedule(Scheduler);

        // -- runs on main thread
        InputDevice.Schedule(Scheduler);

        // -- runs on main thread
        Scheduler.AddTask([this](){
            PT_PROFILE_SCOPE_N("Process Device Inputs");
            if (!ProcessDeviceInput(InputDevice.GetEvents())) {
                Close();
            }
        });

        // -- runs on main thread
        // apply physics result => runtime
        Runtime.Schedule(Scheduler);
        // queue physics command => runtime

        // -- runs on physics thread
        // process physics command => physics
        Physics.Schedule(Scheduler);
        // create physics result => physics

        // -- runs on main thread
        Editor.Schedule(Scheduler);
        RenderExtractor.Schedule(Scheduler);

        // -- runs on render thread
        Renderer.Schedule(Scheduler);

        // -- messaging executes at last on main thread but before swap
        // NOTE: internally any swaps schedule should wait until messaging is processed
        EventBus.Schedule(Scheduler);
        CommandQueue.Schedule(Scheduler);
        RequestQueue.Schedule(Scheduler);

        Scheduler.AddTask([&]() {
            Timing.Wait();
        });

        // -- come back on this later (for job system flow)
        Executor->Execute(Scheduler);
    }

    void Engine::Unload() {}
    void Engine::Shutdown() {}

    bool Engine::ProcessDeviceInput(const Input::InputEvents& events) {
        PT_PROFILE_SCOPE;

        // TODO: migrate to sdl
        // Each loop we will process any events that are waiting for us.
        // SDL_Event event;
        for (const auto& event : events) {
        // while (SDL_PollEvent(&event)) {
            switch (event.type) {


                case SDL_QUIT:
                    Renderer.Shutdown();
                    return false;

                case SDL_KEYDOWN:
                    // If we get a key down event for the ESC key, we also don't want to keep looping.
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        Renderer.Shutdown();

                        // App should close
                        return false;
                    }
                    break;

                // case SDL_USEREVENT:
                    // TODO: use event system here
                    // auto userEvent = static_cast<UserDeviceInputType>(event.user.code);
                    // switch (userEvent) {
                        // case UserDeviceInputType::VIEW_PORT_RESIZE: {
                        //     // MeowEngine::Log("Main Thread", "Rescaled Window");
                        //
                        //     const Vector2Int size = *(Vector2Int *) event.user.data1;
                        //     // Scene->OnWindowResized(size);
                        //     Runtime.GetGameplay().SetViewport(size.Width, size.Height);
                        //     Rendering::RenderCommand::SetViewportSize(size.Width, size.Height);
                        //     break;
                        // }
                        // case UserDeviceInputType::SAVE_PROJECT: {
                        //     CommandQueue.Push(
                        //         Messaging::ThreadType::MAIN,
                        //         std::make_unique<Messaging::SaveProjectCommand>()
                        //     );
                        //     // Scene->Save();
                        // }

                    //     default: ;
                    // }

            }
        }

        // Scene->Input(deltaTime, *InputManager);

        // should app continue?
        return true;
    }

}