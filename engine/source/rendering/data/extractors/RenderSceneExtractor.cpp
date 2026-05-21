//
// Created by Akira Mujawar on 18/05/26.
//

#include <RenderSceneExtractor.hpp>

// core
#include <Public/Threading/Include.hpp>

// handles
#include <ShaderRenderHandle.hpp>
#include <MeshRenderHandle.hpp>
#include <TextureRenderHandle.hpp>

// runtime
#include <GameplaySystem.hpp>
#include <World.hpp>

// editor
#include <Selector.hpp>

// components
#include <mesh_render_component.hpp>
#include <transform3d_component.hpp>
#include <collider_component.hpp>

#include "sky_box_component.hpp"

namespace MeowEngine::Rendering {
    void RenderSceneExtractor::Init(const RenderSceneExtractorInitData& data) {
        Gameplay = data.Gameplay;
        Selector = data.Selector;
    }

    void RenderSceneExtractor::Schedule(Threading::Scheduler& scheduler) {
        // extract draw data for later rendering
        scheduler.AddTask(
            [this]() {
                ExtractRuntime();
            }
        );

        scheduler.AddTask(
            [this]() {
                ExtractEditor();
            }
        );

        // swap buffers (internally only swaps if buffers are not locked)
        scheduler.AddTask(
            [this]() {
                RenderSceneData.Swap();
            }
        );
    }

    // AssetRegistry - uin32_t to path
    // AssetHandle - uint32_t to engine format asset

    // shader program requires vertex shader & fragment shader
    // static mesh requires texture & mesh

    // then referencing becomes questioned
    // - needs individual resolvers for each
    // - or create those combos as another asset file
    // then our project gets bloated with each combo
    //


    void RenderSceneExtractor::ExtractRuntime() {
        auto& world = Gameplay->GetWorld();
        auto& ecs = world.GetRegistry();
        auto& frame = RenderSceneData.GetCurrent();

        // meshes
        auto meshesView = ecs.view<entity::MeshRenderComponent, entity::Transform3DComponent>();
        for (auto &&entity : meshesView) {
            auto&& [mesh, transform] = meshesView.get(entity);
            Rendering::MeshDrawData data;
            data.Shader = ShaderRenderHandle(Asset::AssetHandle::Null, Asset::AssetHandle::Null);
            data.Mesh = MeshRenderHandle(Asset::AssetHandle::Null); // this doesn't exist
            data.Texture = TextureRenderHandle(Asset::AssetHandle::Null); // this doesn't exist
            data.TransformMatrix = transform.TransformMatrix; // this doesnt exist

            frame.Meshes.push_back(data);
        }

        // sky box
        auto skyBox = ecs.try_get<entity::SkyBoxComponent>(world.SkyBox);
        if (skyBox != nullptr) {
            SkyboxDrawData data;
            data.Shader = ShaderRenderHandle(Asset::AssetHandle::Null, Asset::AssetHandle::Null);
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

    void RenderSceneExtractor::ExtractEditor() {
        auto& ecs = Gameplay->GetWorld().GetRegistry();
        auto& frame = RenderSceneData.GetCurrent();

        // selected transform handles
        for (auto &&entity : Selector->SelectedEntities) {
            auto transform = ecs.try_get<entity::Transform3DComponent>(entity);

            if (transform != nullptr) {
                Rendering::TransformHandleDrawData data {};
                // data.Shader = editor.TransformhandelAsset
                data.TransformMatrix = transform->TransformMatrix;

                frame.TransformHandles.push_back(data);
            }
        }

        // grid
        frame.Grid.Shader = ShaderRenderHandle(Asset::AssetHandle::Null, Asset::AssetHandle::Null);
        frame.Grid.TransformMatrix = glm::mat4(1.0f); // camera mvp

        // physics colliders (box, sphere)
        auto&& collidersView = ecs.view<entity::Transform3DComponent, entity::ColliderComponent>();
        for (auto &&entity : collidersView) {
            auto&& [transform, collider] = collidersView.get(entity);

            switch (collider.GetColliderData().GetType()) {
                case entity::ColliderType::BOX: {
                    auto shape = collider.GetColliderData().Cast<entity::BoxColliderShape>();
                    BoxColliderDrawData data;
                    data.Shader = ShaderRenderHandle(Asset::AssetHandle::Null, Asset::AssetHandle::Null);
                    data.TransformMatrix = transform.TransformMatrix; // process collider transform

                    frame.BoxColliders.push_back(data);
                    break;
                }

                case entity::ColliderType::SPHERE: {
                    auto shape = collider.GetColliderData().Cast<entity::SphereColliderShape>();
                    SphereColliderDrawData data;
                    data.Shader = ShaderRenderHandle(Asset::AssetHandle::Null, Asset::AssetHandle::Null);
                    data.TransformMatrix = transform.TransformMatrix; // process collider transform

                    frame.SphereColliders.push_back(data);

                    break;
                }

                default:
                    break;
            }
        }

        // -- examples
        // auto view = registry.view<MeowEngine::core::component::Transform3DComponent>();
        // for(auto entity: view)
        // {
        //     auto transform = view.get<MeowEngine::core::component::Transform3DComponent>(entity);
        //
        // }
        //
        // auto view = registry.view<entity::Transform3dComponent>();
        // registry.view<MeowEngine::entity::Transform3dComponent>().each([](auto entity, auto &MeowEngine::entity::Transform3dComponent) {
        //     // ...
        // });
        //
        // for(auto &&[entt::entity, MeowEngine::entity::Transform3dComponent]: registry.view<entity::Transform3dComponent>().each()) {
        //     // ...
        // }
    }
}
