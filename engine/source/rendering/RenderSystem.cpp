//
// Created by Akira Mujawar on 13/05/26.
//

#include <RenderSystem.hpp>

#include <Public/Threading/Include.hpp>

#include "GraphicsDevice.hpp"


namespace MeowEngine::Rendering {
    RenderSystem::RenderSystem(Graphics::GraphicsDevice& device)
        : WorldViewFrameBuffer(Graphics::GLWorldViewFrameBuffer(1000, 500))
        , EditorRenderPipeline(device)
    {
        MeowEngine::Log("RenderSystem", "Constructed");
    }

    RenderSystem::~RenderSystem() {
        MeowEngine::Log("RenderSystem", "Destructed");
    }

    void RenderSystem::Schedule(Threading::Scheduler& scheduler, Graphics::GraphicsDevice& device) {
        WorldViewFrameBuffer.Bind();
        RuntimeRenderPipeline.BuildGraph(RenderGraph);
        WorldViewFrameBuffer.Unbind();
        EditorRenderPipeline.BuildGraph(RenderGraph);

        scheduler.AddTask(
            [&window = device.GetWindow()]() {
                window.SwapWindow();
            }
        );


        // on update
        // - world view framebuffer bind - renderer
        // - clear gl - renderer
        // - render game view - renderer
        //  - render game view - renderer
        //  - render physics debug - renderer
        // - world view framebuffer unbind - renderer

        // - render editor ui - renderer
        // - clear gl - renderer

        // - window swap - graphics
    }

}
