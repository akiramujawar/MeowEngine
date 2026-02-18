//
// Created by Akira Mujawar on 18/02/26.
//

#include "handle_render_component.hpp"

using MeowEngine::entity::HandleRenderComponent;

void HandleRenderComponent::Reflect() {
    REGISTER_ENUM(HandleRenderComponent, Shader, MeowEngine::assets::ShaderPipelineType, false)
}

HandleRenderComponent::HandleRenderComponent()
    : MeowEngine::entity::RenderComponentBase(MeowEngine::assets::ShaderPipelineType::TRANSFORM_HANDLE) {
}

HandleRenderComponent::HandleRenderComponent(MeowEngine::assets::ShaderPipelineType shaderPipelineType)
    : MeowEngine::entity::RenderComponentBase(shaderPipelineType) {

}