//
// Created by Akira Mujawar on 22/02/26.
//

#include <EditorRenderPipeline.hpp>

#include <Public/MeowEditor.hpp>

#include "EditorModule.hpp"

namespace MeowEngine::Editor {

    RenderPipeline::RenderPipeline(Graphics::GraphicsDevice& device)
    : UI(device)
    {}

    RenderPipeline::~RenderPipeline() {}

    void RenderPipeline::BuildGraph(Rendering::RenderGraph& graph) {
        // TODO: we remove this dependency
        UI.Render(
            Editor::GetEditor().GetInputBuffer().GetCurrent()
            , Editor::GetEditor().GetInputBuffer().GetPropertyChangeQueue()
            , Editor::GetEditor().GetSelector()
            , 0, 0
        );
    }
}


