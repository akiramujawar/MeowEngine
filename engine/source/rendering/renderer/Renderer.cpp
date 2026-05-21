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

        Device = context.Device;
        Context.PipelineManager = &PipelineManager;
        Context.ResourceManager = &ResourceManager;
    }

    void Renderer::Schedule(Threading::Scheduler& scheduler, RenderSceneExtractor& extractor) {
        // RenderContext context {
        //     PipelineManager,
        //     ResourceManager,
        //     extractor.GetRenderFrameData().GetFinal()
        // };

        Context.SceneData = &extractor.GetRenderFrameData().GetFinal();
        Context.PipelineManager->abc = 1000;

        Scene.Schedule(scheduler, Context);
        UI.Schedule(scheduler);

        scheduler.AddTask(
            [&window = Device->GetWindow()]() {
                window.SwapWindow();
            }
        );
    }
}
