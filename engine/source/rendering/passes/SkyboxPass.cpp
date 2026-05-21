//
// Created by Akira Mujawar on 20/05/26.
//

#include <SkyboxPass.hpp>
#include <log.hpp>

#include <RenderContext.hpp>
#include <RenderSceneData.hpp>
#include <RenderPipelineManager.hpp>
#include <GLSkyboxPipeline.hpp>

namespace MeowEngine::Rendering {
    SkyboxPass::SkyboxPass() {}

    SkyboxPass::~SkyboxPass() {}

    void SkyboxPass::Draw(RenderContext& context) {
        const auto& pipeline = context.PipelineManager->GetPipeline<GLSkyboxPipeline>();
        pipeline.Draw(context, context.SceneData->Skybox);
    }
}
