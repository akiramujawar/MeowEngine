//
// Created by Akira Mujawar on 13/05/26.
//

#include <WorldRenderer.hpp>

#include <Public/Threading/Include.hpp>

#include <GraphicsDevice.hpp>
#include <RenderCommand.hpp>

#include "RendererContext.hpp"


namespace MeowEngine::Rendering {
    WorldRenderer::WorldRenderer()
        : WorldViewFrameBuffer(Graphics::GLWorldViewFrameBuffer(1000, 500))
    {
        MeowEngine::Log("Renderer", "Constructed");
    }

    WorldRenderer::~WorldRenderer() {
        MeowEngine::Log("Renderer", "Destructed");
    }

    void WorldRenderer::Init(RendererContext& context) {
        RuntimeBuilder.Init();
        EditorBuilder.Init();
    }

    void WorldRenderer::Schedule(Threading::Scheduler& scheduler) {
        RenderGraph.Clear();

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

        RuntimeBuilder.BuildGraph(RenderGraph);
        EditorBuilder.BuildGraph(RenderGraph);

        scheduler.AddTask(
            [this]() {
                WorldViewFrameBuffer.Unbind();
            }
        );

        scheduler.AddTask(
            [&]() {
                RenderGraph.Execute();
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
