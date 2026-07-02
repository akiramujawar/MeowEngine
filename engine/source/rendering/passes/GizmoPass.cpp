//
// Created by Akira Mujawar on 20/05/26.
//

#include <GizmoPass.hpp>
#include <RenderSceneData.hpp>

#include "GLTransformGizmoPipeline.hpp"
#include "RenderContext.hpp"
#include "RenderPipelineManager.hpp"

namespace MeowEngine::Rendering {
    GizmoPass::GizmoPass() {}

    GizmoPass::~GizmoPass() {}

    void GizmoPass::Draw(RenderContext& context) {
        auto& gizmoTransformPipeline = context.PipelineManager->GetPipeline<GLTransformGizmoPipeline>();

        for (auto& gizmo : context.SceneData->TransformGizmos) {
            gizmoTransformPipeline.Draw(context, gizmo);
        }
        // get shader program
        // draw
        // data.Grid.VertexShader

        // get pipeline.Draw(shader, mesh, texture)
        // shader (vertex asset + frag asset)
        // mesh
        // texture
    }
}
