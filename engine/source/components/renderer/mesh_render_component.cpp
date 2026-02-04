//
// Created by Akira Mujawar on 23/06/24.
//

#include "mesh_render_component.hpp"
#include <log.hpp>
#include "entt_reflection_wrapper.hpp"

using MeowEngine::entity::MeshRenderComponent;

void MeowEngine::entity::MeshRenderComponent::Reflect() {
    MeowEngine::Log("Reflected", "MeshRenderComponent");
}

MeshRenderComponent::MeshRenderComponent(MeowEngine::assets::ShaderPipelineType shader, MeowEngine::StaticMeshInstance *meshInstance)
    : MeshInstance(meshInstance) {
    Shader = shader;
}