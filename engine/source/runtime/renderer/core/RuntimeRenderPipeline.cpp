//
// Created by Akira Mujawar on 21/06/24.
//

#include <RuntimeRenderPipeline.hpp>
#include <log.hpp>

#include "RenderGraph.hpp"

namespace MeowEngine::Runtime {
    RenderPipeline::RenderPipeline() {
        MeowEngine::Log("Runtime RenderPipeline", "Constructed");
    }

    RenderPipeline::~RenderPipeline() {
        MeowEngine::Log("Runtime RenderPipeline", "Destructed");
    }

    void RenderPipeline::Render() {

    }

}
