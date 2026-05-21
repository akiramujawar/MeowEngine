//
// Created by Akira Mujawar on 21/06/24.
//

#include <RuntimeSceneBuilder.hpp>
#include <log.hpp>

#include <RenderGraph.hpp>

#include "GeometryPassData.hpp"


namespace MeowEngine::Runtime {
    RuntimeSceneBuilder::RuntimeSceneBuilder() {
        MeowEngine::Log("Runtime RenderPipeline", "Constructed");
    }

    RuntimeSceneBuilder::~RuntimeSceneBuilder() {
        MeowEngine::Log("Runtime RenderPipeline", "Destructed");
    }

    void RuntimeSceneBuilder::Init() {}

    void RuntimeSceneBuilder::BuildGraph(Rendering::RenderGraph& graph) {
        Add<Rendering::GeometryPassData>
    }
}
