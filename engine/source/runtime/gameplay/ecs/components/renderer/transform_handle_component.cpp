//
// Created by Akira Mujawar on 18/02/26.
//

#include "transform_handle_component.hpp"

using MeowEngine::Runtime::TransformHandleComponent;

void TransformHandleComponent::Reflect() {
    REGISTER_ENUM(TransformHandleComponent, Shader, MeowEngine::assets::ShaderPipelineType, false)
}

TransformHandleComponent::TransformHandleComponent()
    : MeowEngine::Runtime::RenderComponentBase(MeowEngine::assets::ShaderPipelineType::TRANSFORM_HANDLE) {
}

TransformHandleComponent::TransformHandleComponent(MeowEngine::assets::ShaderPipelineType shaderPipelineType)
    : MeowEngine::Runtime::RenderComponentBase(shaderPipelineType) {

}