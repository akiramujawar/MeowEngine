//
// Created by Akira Mujawar on 23/06/24.
//

#include "mesh_render_component.hpp"
#include <log.hpp>

using MeowEngine::entity::MeshRenderComponent;

void MeowEngine::entity::MeshRenderComponent::Reflect() {
    REGISTER_POINTER(MeshRenderComponent, MeshInstance, MeowEngine::StaticMeshInstance*, false, false)
}

MeshRenderComponent::MeshRenderComponent(MeowEngine::assets::ShaderPipelineType shader, MeowEngine::StaticMeshInstance *meshInstance)
    : MeshInstance(meshInstance) {
    Shader = shader;
}