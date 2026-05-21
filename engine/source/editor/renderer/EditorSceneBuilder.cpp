//
// Created by Akira Mujawar on 22/02/26.
//

#include <EditorSceneBuilder.hpp>
#include <log.hpp>

#include <RenderGraph.hpp>
#include <RenderSceneData.hpp>

#include <GizmoPass.hpp>

namespace MeowEngine::Editor {

    EditorSceneBuilder::EditorSceneBuilder() {
        MeowEngine::Log("RenderPipeline", "Constructed");
    }

    EditorSceneBuilder::~EditorSceneBuilder() {
        MeowEngine::Log("RenderPipeline", "Destructed");
    }

    void EditorSceneBuilder::Init() {}

    void EditorSceneBuilder::BuildGraph(Rendering::RenderGraph& graph) {
        graph.Add<Rendering::GizmoPass>();
    }
}


