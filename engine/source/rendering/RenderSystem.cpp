//
// Created by Akira Mujawar on 13/05/26.
//

#include <RenderSystem.hpp>

namespace MeowEngine::Rendering {
    RenderSystem::RenderSystem() {}
    RenderSystem::~RenderSystem() {}

    void RenderSystem::Schedule(Scheduler& scheduler) {
        RuntimeRenderPipeline.BuildGraph(RenderGraph);
        EditorRenderPipeline.BuildGraph(RenderGraph);
    }

}
