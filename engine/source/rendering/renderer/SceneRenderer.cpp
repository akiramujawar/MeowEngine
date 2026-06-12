//
// Created by Akira Mujawar on 13/05/26.
//

#include <SceneRenderer.hpp>

#include <Public/Threading/Include.hpp>

#include <RendererInitData.hpp>
#include <GraphicsDevice.hpp>
#include <RenderCommand.hpp>

#include <SkyBoxPass.hpp>
#include <EditorOverlayPass.hpp>
#include <GeometryPass.hpp>
#include <WorldUIPass.hpp>
#include <DebugPass.hpp>
#include <GizmoPass.hpp>
#include <PostProcessPass.hpp>

#include "RenderContext.hpp"

namespace MeowEngine::Rendering {
    SceneRenderer::SceneRenderer()
        : SceneViewFrameBuffer(Graphics::GLWorldViewBuffer(1000, 500))
    {
        MeowEngine::Log("Renderer", "Constructed");
    }

    SceneRenderer::~SceneRenderer() {
        MeowEngine::Log("Renderer", "Destructed");
    }

    void SceneRenderer::Init(RendererInitData& context) {
        RuntimeSceneBuilder.Init();
        EditorSceneBuilder.Init();
    }

    void SceneRenderer::Schedule(Threading::Scheduler& scheduler, RenderContext& renderContext) {
        scheduler.AddTask(
            [this]() {
                SceneViewFrameBuffer.Bind();
            }
        );

        scheduler.AddTask(
            []() {
                RenderCommand::Clear();
            }
        );

        // scheduler.AddTask({
        //     [] {
        //
        //     }
        // });


        scheduler.AddTask(
            [this, &renderContext]() {
                renderContext.SceneData = &renderContext.Extractor->GetRenderSceneData().GetFinal();

                RenderGraph.Clear();

                RenderGraph.Add<SkyboxPass>();
                RenderGraph.Add<EditorOverlayPass>();
                RenderGraph.Add<GeometryPass>();
                RenderGraph.Add<DebugPass>();
                RenderGraph.Add<PostProcessPass>();
                RenderGraph.Add<GizmoPass>();

                RenderGraph.Execute(renderContext);
            }
        );

        scheduler.AddTask(
            [this]() {
                SceneViewFrameBuffer.Unbind();
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

    void SceneRenderer::Shutdown() {}
}
