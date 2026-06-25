//
// Created by Akira Mujawar on 12/06/26.
//

#include <RenderRuntimeExtractor.hpp>

#include <RenderSceneData.hpp>
#include <RenderUIData.hpp>

// runtime
#include <GameplaySystem.hpp>
#include <World.hpp>

// components
#include <mesh_render_component.hpp>
#include <transform3d_component.hpp>
#include "sky_box_component.hpp"

namespace MeowEngine::Rendering {
    void RenderRuntimeExtractor::Init(const RenderExtractorInitData& frame) {
        Gameplay = frame.Gameplay;
        Selector = frame.Selector;
    }

    void RenderRuntimeExtractor::ExtractScene(RenderSceneData& frame) {
        auto& world = Gameplay->GetWorld();
        auto& ecs = world.GetRegistry();

        // meshes
        auto meshesView = ecs.view<Runtime::MeshRenderComponent, Runtime::Transform3DComponent>();
        for (auto &&entity : meshesView) {
            auto&& [mesh, transform] = meshesView.get(entity);
            Rendering::MeshDrawData data;
            data.Shader = ShaderRenderHandle(Asset::AssetHandle::Invalid);
            data.Mesh = MeshRenderHandle(Asset::AssetHandle::Invalid); // this doesn't exist
            data.Texture = TextureRenderHandle(Asset::AssetHandle::Invalid); // this doesn't exist
            data.TransformMatrix = transform.TransformMatrix; // this doesnt exist

            frame.Meshes.push_back(data);
        }

        // access grid component
        // access shader asset handle
        // load shader using asset manager
        // create shader render handle
        // if cannot load
        // assign invalid handle

        // sky box
        auto skyBox = ecs.try_get<Runtime::SkyBoxComponent>(world.SkyBox.GetEntity());
        if (skyBox != nullptr) {
            SkyboxDrawData data;
            data.Shader = ShaderRenderHandle(Asset::AssetHandle::Invalid);
            data.TransformMatrix = glm::mat4(1.0f); // camera

            frame.Skybox = data;
        }

        // -- gameplay
        // mesh
        // textures
        // skybox

        // -- editor
        // gizmos
        // colliders
        // lines
        // grid - do we need this as a entity to process? it is a pure shader and only requires camera projection etc...?
    }

    void RenderRuntimeExtractor::ExtractUI(RenderUIData& frame) {

    }

    void RenderRuntimeExtractor::Clear(RenderSceneData& sceneFrame, RenderUIData& uiFrame) {
        // clear scene data
        sceneFrame.Meshes.clear();

        // clear ui data

    }
}
