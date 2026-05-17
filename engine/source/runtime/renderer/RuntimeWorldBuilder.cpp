//
// Created by Akira Mujawar on 21/06/24.
//

#include <RuntimeWorldBuilder.hpp>
#include <log.hpp>

#include <RenderGraph.hpp>

namespace MeowEngine::Runtime {
    RuntimeWorldBuilder::RuntimeWorldBuilder() {
        MeowEngine::Log("Runtime RenderPipeline", "Constructed");
    }

    RuntimeWorldBuilder::~RuntimeWorldBuilder() {
        MeowEngine::Log("Runtime RenderPipeline", "Destructed");
    }

    void RuntimeWorldBuilder::Init() {}
    void RuntimeWorldBuilder::BuildGraph(Rendering::RenderGraph& graph) {}
}
