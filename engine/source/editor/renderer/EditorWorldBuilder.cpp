//
// Created by Akira Mujawar on 22/02/26.
//

#include <EditorWorldBuilder.hpp>
#include <log.hpp>

namespace MeowEngine::Editor {

    EditorWorldBuilder::EditorWorldBuilder() {
        MeowEngine::Log("RenderPipeline", "Constructed");
    }

    EditorWorldBuilder::~EditorWorldBuilder() {
        MeowEngine::Log("RenderPipeline", "Destructed");
    }

    void EditorWorldBuilder::Init() {}

    void EditorWorldBuilder::BuildGraph(Rendering::RenderGraph& graph) {}
}


