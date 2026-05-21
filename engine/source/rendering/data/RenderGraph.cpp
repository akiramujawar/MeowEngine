//
// Created by Akira Mujawar on 13/05/26.
//

#include <RenderGraph.hpp>

#include <IRenderPass.hpp>

namespace MeowEngine::Rendering {

    RenderGraph::RenderGraph() {}

    RenderGraph::~RenderGraph() {}

    void RenderGraph::Clear() {
        RenderPasses.clear();
    }

    void RenderGraph::Execute(RenderContext& renderContext) {
        for (auto& pass : RenderPasses) {
            pass->Draw(renderContext);
        }
    }
}
