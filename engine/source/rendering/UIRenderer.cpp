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

#include <RendererContext.hpp>

namespace MeowEngine::Rendering {
    UIRenderer::UIRenderer() = default;
    UIRenderer::~UIRenderer() = default;

    void UIRenderer::Init(RendererContext& context) {
        Backend = std::make_unique<ImGuiRender>(*context.Device);

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

}
