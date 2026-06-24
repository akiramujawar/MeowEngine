//
// Created by Akira Mujawar on 19/02/26.
//

#include "grid_component.hpp"

namespace MeowEngine::Runtime {
    using Asset::AssetHandle;

    void GridComponent::Reflect() {
        REGISTER_ENUM(GridComponent, Shader, MeowEngine::assets::ShaderPipelineType, false)
        REGISTER_PROPERTY(GridComponent, FragmentShader, AssetHandle, true, false);
        REGISTER_PROPERTY(GridComponent, VertexShader, AssetHandle, true, false);
    }

    GridComponent::GridComponent() : MeowEngine::Runtime::RenderComponentBase(
            MeowEngine::assets::ShaderPipelineType::Grid)
    {}

    GridComponent::GridComponent(MeowEngine::assets::ShaderPipelineType shaderPipelineType)
            : MeowEngine::Runtime::RenderComponentBase(shaderPipelineType)
    {}

} // MeowEngine::component