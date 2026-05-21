//
// Created by Akira Mujawar on 22/02/26.
//

#include <EditorSceneBuilder.hpp>
#include <log.hpp>

namespace MeowEngine::Editor {

    EditorSceneBuilder::EditorSceneBuilder() {
        MeowEngine::Log("RenderPipeline", "Constructed");
    }

    EditorSceneBuilder::~EditorSceneBuilder() {
        MeowEngine::Log("RenderPipeline", "Destructed");
    }

    void EditorSceneBuilder::Init() {}

}


