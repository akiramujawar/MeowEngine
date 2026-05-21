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
    }

    void Renderer::Schedule(Threading::Scheduler& scheduler, RenderSceneExtractor& extractor) {
        RenderContext context {
            PipelineManager,
            ResourceManager,
            extractor.GetRenderFrameData().GetFinal()
        };

        Scene.Schedule(scheduler, context);
        UI.Schedule(scheduler);

        scheduler.AddTask(
            [&window = Device->GetWindow()]() {
                window.SwapWindow();
            }
        );
    }
}
