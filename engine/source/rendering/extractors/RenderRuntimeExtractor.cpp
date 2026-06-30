//
// Created by Akira Mujawar on 12/06/26.
//

#include <RenderRuntimeExtractor.hpp>

#include <RenderSceneData.hpp>
#include <RenderUIData.hpp>
#include "ShaderAsset.hpp"

// core
#include "Math.hpp"

// runtime
#include "AssetManager.hpp"
#include <GameplaySystem.hpp>
#include <World.hpp>

// components
#include <mesh_render_component.hpp>
#include <Transform3DComponent.hpp>
#include "SkyBoxComponent.hpp"
#include "CameraComponent.hpp"

namespace MeowEngine::Rendering {
    void RenderRuntimeExtractor::Init(const RenderExtractorInitData& frame) {
        Gameplay = frame.Gameplay;
        Selector = frame.Selector;
        AssetManager = frame.AssetManager;
    }

    void RenderRuntimeExtractor::ExtractScene(RenderSceneData& frame) {
        auto& world = Gameplay->GetWorld();
        auto& ecs = world.GetRegistry();
        const auto& camera = Gameplay->GetCamera();

        // meshes
        auto meshesView = ecs.view<Runtime::MeshRenderComponent, Runtime::Transform3DComponent>();
        for (auto &&entity : meshesView) {
            auto&& [mesh, transform] = meshesView.get(entity);
            Rendering::MeshDrawData data;
            data.Shader = ShaderRenderHandle(Asset::AssetHandle::Invalid);
            data.Mesh = MeshRenderHandle(Asset::AssetHandle::Invalid); // this doesn't exist
            data.Texture = TextureRenderHandle(Asset::AssetHandle::Invalid); // this doesn't exist
            data.TransformMatrix = camera.GetViewProjection() * transform.ToMatrix(); // this doesnt exist

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
            if (AssetManager->HasAssetInDatabase(skyBox->GetShaderAssetHandle())) {
                AssetManager->GetAssetOrLoad<Asset::ShaderAsset>(skyBox->GetShaderAssetHandle());

                SkyboxDrawData data;
                data.Shader = ShaderRenderHandle(skyBox->GetShaderAssetHandle());
                data.CameraViewMatrix = camera.GetView(); // camera
                data.CameraProjectionMatrix = camera.GetProjection(); // camera

                frame.Skybox = data;
            }
            else {
                SkyboxDrawData data;
                data.Shader = ShaderRenderHandle(Asset::AssetHandle::Invalid);

                frame.Skybox = data;
            }
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
