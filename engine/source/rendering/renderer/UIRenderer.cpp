//
// Created by Akira Mujawar on 16/05/26.
//

#include <UIRenderer.hpp>

#include <Public/Threading/Include.hpp>
#include <RenderCommand.hpp>
#include <ImGuiRender.hpp>

// NOTE: remove this later
#include <EditorModule.hpp>
#include <Public/MeowEditor.hpp>

#include <RendererInitData.hpp>
#include <UserDeviceInputType.hpp>

namespace MeowEngine::Rendering {
    UIRenderer::UIRenderer() = default;
    UIRenderer::~UIRenderer() = default;

    void UIRenderer::Init(RendererInitData& context) {
        InputDevice = context.InputDevice;
        Backend = std::make_unique<ImGuiRender>(*context.GraphicsDevice);

        RuntimeBuilder.Init();
        EditorBuilder.Init(*context.Gameplay);
    }

    void UIRenderer::Schedule(Threading::Scheduler& scheduler) {
        // RuntimeBuilder.Input();
        // EditorBuilder.Input();

        scheduler.AddTask(
            []() {
                RenderCommand::Clear();
            }
        );

        scheduler.AddTask(
            [&]() {
                Backend->BeginFrame();
            }
        );

        // schedule ui
        scheduler.AddTask(
            [&]() {
                ProcessDeviceInput(InputDevice->GetEvents().GetCurrent());
            }
        );

        scheduler.AddTask(
            [&]() {
                EditorBuilder.BuildDrawData(
                    Editor::GetEditor().GetInputBuffer().GetCurrent()
                    , Editor::GetEditor().GetInputBuffer().GetPropertyChangeQueue()
                    , Editor::GetEditor().GetSelector()
                    , 0, 0
                );
            }
        );

        RuntimeBuilder.BuildDrawData();

        scheduler.AddTask(
            [&]() {
                Backend->EndFrame();
            }
        );

        scheduler.AddTask(
            [&]() {
                Backend->DrawFrame();
            }
        );
    }

    void UIRenderer::Shutdown() {
        EditorBuilder.CloseProcesses();
    }

    void UIRenderer::ProcessDeviceInput(const Input::InputEvents& events) {
        PT_PROFILE_SCOPE_N("UI Input");

        for (const auto& event : events) {
            Backend->ProcessInputEvent(event);

            // custom user platform
#ifdef _WIN32
            if (event.type == SDL_SYSWMEVENT) {
                if (event.syswm.msg->msg.win.msg == WM_COMMAND) {
                    switch (LOWORD(event.syswm.msg->msg.win.wParam)) {
                        case 1:
                            std::cout << "Option 1 selected" << std::endl;
                            break;
                    }
                }
            }
#endif

#ifdef __APPLE__
            if (event.type == SDL_USEREVENT) {
                switch (event.user.code) {
                    case UserDeviceInputType::OPEN_TRACY:
                        EditorBuilder.OpenProfiler();
                        break;
                }
            }
#endif
        }
    }
}
