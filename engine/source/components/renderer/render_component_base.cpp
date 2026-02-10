//
// Created by Akira Mujawar on 23/06/24.
//

#include "render_component_base.hpp"
#include <log.hpp>

using MeowEngine::entity::RenderComponentBase;

void MeowEngine::entity::RenderComponentBase::Reflect() {
    REGISTER_ENUM(RenderComponentBase, Shader, MeowEngine::assets::ShaderPipelineType);
}

RenderComponentBase::RenderComponentBase()
    : Shader(MeowEngine::assets::ShaderPipelineType::Default) {}

RenderComponentBase::RenderComponentBase(MeowEngine::assets::ShaderPipelineType shaderPipelineType)
    : Shader(shaderPipelineType) {}
