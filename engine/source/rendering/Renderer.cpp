//
// Created by Akira Mujawar on 13/05/26.
//

#include <Renderer.hpp>

#include <Public/Threading/Include.hpp>

#include <GraphicsDevice.hpp>
#include <RenderCommand.hpp>


namespace MeowEngine::Rendering {
    Renderer::Renderer(Graphics::GraphicsDevice& device)
        : WorldViewFrameBuffer(Graphics::GLWorldViewFrameBuffer(1000, 500))
        , EditorRenderPipeline(device)
    {
        MeowEngine::Log("Renderer", "Constructed");
    }

    Renderer::~Renderer() {
        MeowEngine::Log("Renderer", "Destructed");
    }

    void Renderer::Schedule(Threading::Scheduler& scheduler, Graphics::GraphicsDevice& device) {
        scheduler.AddTask(
            [this]() {
                WorldViewFrameBuffer.Bind();
            }
        );

        scheduler.AddTask(
            []() {
                RenderCommand::Clear();
            }
        );

        RuntimeRenderPipeline.BuildGraph(RenderGraph);

        scheduler.AddTask(
            [this]() {
                WorldViewFrameBuffer.Unbind();
            }
        );

        scheduler.AddTask(
            []() {
                RenderCommand::Clear();
            }
        );

        scheduler.AddTask(
            [this]() {
                EditorRenderPipeline.BuildGraph(RenderGraph);
            }
        );

        scheduler.AddTask(
            [&window = device.GetWindow()]() {
                window.SwapWindow();
            }
        );

        // on update
        // - world view framebuffer bind - root - done
        // - clear gl - root - done
        // - render game - runtime renderer
        //    - render game view - runtime renderer
        //    - render physics debug - runtime renderer
        //    - render game ui - runtime renderer
        // - world view framebuffer unbind - root - done
        // - render editor ui - editor renderer - done
        // - clear gl - root - done

        // - window swap - graphics
    }

}
