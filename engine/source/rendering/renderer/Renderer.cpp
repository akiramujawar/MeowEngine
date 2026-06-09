//
// Created by Akira Mujawar on 17/05/26.
//

#include "Renderer.hpp"

#include <RendererInitData.hpp>
#include <RenderContext.hpp>

#include <RenderSceneExtractor.hpp>

namespace MeowEngine::Rendering {
    Renderer::Renderer() {}
    Renderer::~Renderer() {}

    void Renderer::Init(RendererInitData& context) {
        Scene.Init(context);
        UI.Init(context);

        GraphicsDevice = context.GraphicsDevice;
        Context.PipelineManager = &PipelineManager;
        Context.ResourceManager = &ResourceManager;
    }

    void Renderer::Schedule(Threading::Scheduler& scheduler, RenderSceneExtractor& extractor) {
        Context.SceneData = &extractor.GetRenderFrameData().GetFinal();

        Scene.Schedule(scheduler, Context);
        UI.Schedule(scheduler);

        scheduler.AddTask(
            [&window = GraphicsDevice->GetWindow()]() {
                window.SwapWindow();
            }
        );
    }

    void Renderer::Shutdown() {
        // If we get a quit signal, we will return that we don't want to keep looping.
        // RenderThread->UserInterface->ClosePIDs();
        Scene.Shutdown();
        UI.Shutdown();
    }
}
