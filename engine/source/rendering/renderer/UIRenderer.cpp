//
// Created by Akira Mujawar on 16/05/26.
//

#include <UIRenderer.hpp>

#include <Public/Threading/Include.hpp>
#include <RenderCommand.hpp>
#include <ImGuiRender.hpp>

// NOTE: remove this later
#include <EditorModule.hpp>

#include <RendererInitData.hpp>
#include <UserDeviceInputType.hpp>

#include "MeowService.hpp"
#include "EventBus.hpp"
#include "RenderContext.hpp"
#include "EventContainer.hpp"

namespace MeowEngine::Rendering {
    UIRenderer::UIRenderer() {
        MeowEngine::Log("UIRenderer", "Constructed");
    };
    UIRenderer::~UIRenderer() {
        MeowEngine::Log("UIRenderer", "Destructed");
    };

    void UIRenderer::Init(RendererInitData& context) {
        InputDevice = context.InputDevice;
        Backend = std::make_unique<ImGuiRender>(*context.GraphicsDevice);
        Backend->Init(context);

        RuntimeBuilder.Init();
        EditorBuilder.Init(*context.Gameplay);
    }

    void UIRenderer::SubscribeToEvents() {
        MeowService().EventBus.Subscribe<Messaging::SaveProjectEvent>(
           [&](const Messaging::SaveProjectEvent& event) {
               Backend->SaveLayout();
           }
       );

        MeowService().EventBus.Subscribe<Messaging::OpenFrameProfiler>(
          [&](const Messaging::OpenFrameProfiler& event) {
              EditorBuilder.OpenProfiler();
          }
      );
    }

    void UIRenderer::Schedule(Threading::Scheduler& scheduler, RenderContext& renderContext) {
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
                // TODO: remove this and replace with command queue
                ProcessDeviceInput(InputDevice->GetEvents());
            }
        );

        scheduler.AddTask(
            [&]() {
                renderContext.UIData = &renderContext.Extractor->GetRenderUIData().GetRead();

                EditorBuilder.BuildDrawData(
                    renderContext
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
        }
    }
}
