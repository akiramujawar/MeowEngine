//
// Created by Akira Mujawar on 20/05/26.
//

#include <GeometryPass.hpp>
#include <RenderSceneData.hpp>

#include "GLMeshPipeline.hpp"
#include "RenderContext.hpp"
#include "RenderPipelineManager.hpp"

namespace MeowEngine::Rendering {
    GeometryPass::GeometryPass() {}

    GeometryPass::~GeometryPass() {}

    void GeometryPass::Draw(RenderContext& context) {
        auto& meshPipeline = context.PipelineManager->GetPipeline<GLMeshPipeline>();
        for (auto& mesh : context.SceneData->Meshes) {
            meshPipeline.Draw(context, mesh);
        }
    }
}
