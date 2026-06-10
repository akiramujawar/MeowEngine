//
// Created by Akira Mujawar on 13/05/26.
//

#include <RenderSceneGraph.hpp>

#include <IRenderPass.hpp>

namespace MeowEngine::Rendering {

    RenderSceneGraph::RenderSceneGraph() {}

    RenderSceneGraph::~RenderSceneGraph() {}

    void RenderSceneGraph::Clear() {
        RenderPasses.clear();
    }

    void RenderSceneGraph::Execute(RenderContext& renderContext) {
        for (auto& pass : RenderPasses) {
            pass->Draw(renderContext);
        }
    }
}
