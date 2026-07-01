//
// Created by Akira Mujawar on 20/05/26.
//

#include <GeometryPass.hpp>
#include <RenderSceneData.hpp>

#include "opengl_mesh_pipeline.hpp"
#include "RenderContext.hpp"
#include "RenderPipelineManager.hpp"
#include "opengl_mesh_pipeline.hpp"

namespace MeowEngine::Rendering {
    GeometryPass::GeometryPass() {}

    GeometryPass::~GeometryPass() {}

    void GeometryPass::Draw(RenderContext& context) {
        auto& meshPipeline = context.PipelineManager->GetPipeline<OpenGLMeshPipeline>();
        for (auto& mesh : context.SceneData->Meshes) {
            meshPipeline.Draw(context, mesh);
        }
    }
}
