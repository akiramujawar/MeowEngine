//
// Created by Akira Mujawar on 23/06/24.
//

#include "sky_box_component.hpp"
#include <log.hpp>

using MeowEngine::Runtime::SkyBoxComponent;

void MeowEngine::Runtime::SkyBoxComponent::Reflect() {
    REGISTER_ENUM(SkyBoxComponent, Shader, MeowEngine::assets::ShaderPipelineType, false)
}

SkyBoxComponent::SkyBoxComponent()
    : MeowEngine::Runtime::RenderComponentBase(MeowEngine::assets::ShaderPipelineType::Default) {}

SkyBoxComponent::SkyBoxComponent(MeowEngine::assets::ShaderPipelineType shaderPipelineType)
    : MeowEngine::Runtime::RenderComponentBase(shaderPipelineType) {}
