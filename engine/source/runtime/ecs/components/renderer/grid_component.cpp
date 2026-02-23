//
// Created by Akira Mujawar on 19/02/26.
//

#include "grid_component.hpp"

namespace MeowEngine::component {

    void GridComponent::Reflect() {
        REGISTER_ENUM(GridComponent, Shader, MeowEngine::assets::ShaderPipelineType, false)
    }

    GridComponent::GridComponent() : MeowEngine::entity::RenderComponentBase(
            MeowEngine::assets::ShaderPipelineType::Grid
    ){

    }

    GridComponent::GridComponent(MeowEngine::assets::ShaderPipelineType shaderPipelineType)
            : MeowEngine::entity::RenderComponentBase(shaderPipelineType) {

    }

} // MeowEngine::component