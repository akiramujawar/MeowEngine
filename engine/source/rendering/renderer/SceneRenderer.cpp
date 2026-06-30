//
// Created by Akira Mujawar on 13/05/26.
//

#include <SceneRenderer.hpp>

#include <Public/Threading/Include.hpp>

#include <RendererInitData.hpp>
#include <GraphicsDevice.hpp>
#include <RenderCommand.hpp>
#include "WorldFrameBufferScope.hpp"

#include <SkyBoxPass.hpp>
#include <EditorOverlayPass.hpp>
#include <GeometryPass.hpp>
#include <WorldUIPass.hpp>
#include <DebugPass.hpp>
#include <GizmoPass.hpp>
#include <PostProcessPass.hpp>

#include "RenderContext.hpp"

namespace MeowEngine::Rendering {
    SceneRenderer::SceneRenderer() {
        MeowEngine::Log("SceneRenderer", "Constructed");
    }

    SceneRenderer::~SceneRenderer() {
        MeowEngine::Log("SceneRenderer", "Destructed");
    }

    void SceneRenderer::Init(RendererInitData& context) {
        RuntimeSceneBuilder.Init();
        EditorSceneBuilder.Init();

        RenderGraph.Clear();
        RenderGraph.Add<SkyboxPass>();
        RenderGraph.Add<EditorOverlayPass>();
        RenderGraph.Add<GeometryPass>();
        RenderGraph.Add<DebugPass>();
        RenderGraph.Add<PostProcessPass>();
        RenderGraph.Add<GizmoPass>();
    }

    void SceneRenderer::Schedule(Threading::Scheduler& scheduler, RenderContext& renderContext) {


        scheduler.AddTask(
            [this, &renderContext]() {
                PT_PROFILE_SCOPE_N("Scene Render");
                renderContext.SceneData = &renderContext.Extractor->GetRenderSceneData().GetRead();

                WorldFrameBufferScope scope(RenderCommand::GetSceneFrameBuffer());
                RenderCommand::Clear();
                RenderGraph.Execute(renderContext);
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
