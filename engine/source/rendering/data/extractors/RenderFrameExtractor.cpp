//
// Created by Akira Mujawar on 18/05/26.
//

#include <RenderFrameExtractor.hpp>

// core
#include <Public/Threading/Include.hpp>

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
    void RenderFrameExtractor::Init(const RenderFrameExtractorInitData& data) {
        Gameplay = data.Gameplay;
        Selector = data.Selector;
    }

    void RenderFrameExtractor::Schedule(Threading::Scheduler& scheduler) {
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
                RenderFrameData.Swap();
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


    void RenderFrameExtractor::ExtractRuntime() {
        auto& world = Gameplay->GetWorld();
        auto& ecs = world.GetRegistry();
        auto& frame = RenderFrameData.GetCurrent();

        // meshes
        auto meshesView = ecs.view<entity::MeshRenderComponent, entity::Transform3DComponent>();
        for (auto &&entity : meshesView) {
            auto&& [mesh, transform] = meshesView.get(entity);
            Rendering::MeshDrawData data;
            data.VertexShader = Asset::AssetHandle::Null;
            data.FragmentShader = Asset::AssetHandle::Null;
            data.Mesh = Asset::AssetHandle::Null; // this doesn't exist
            data.TransformMatrix = transform.TransformMatrix; // this doesnt exist

            frame.Meshes.push_back(data);
        }

        // sky box
        auto skyBox = ecs.try_get<entity::SkyBoxComponent>(world.SkyBox);
        if (skyBox != nullptr) {
            SkyBoxDrawData data;
            data.VertexShader = Asset::AssetHandle::Null;
            data.FragmentShader = Asset::AssetHandle::Null;
            data.TransformMatrix = glm::mat4(1.0f); // camera

            frame.SkyBox = data;
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

    void RenderFrameExtractor::ExtractEditor() {
        auto& ecs = Gameplay->GetWorld().GetRegistry();
        auto& frame = RenderFrameData.GetCurrent();

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
        frame.Grid.VertexShader = Asset::AssetHandle::Null;
        frame.Grid.FragmentShader = Asset::AssetHandle::Null;
        frame.Grid.TransformMatrix = glm::mat4(1.0f); // camera mvp

        // physics colliders (box, sphere)
        auto&& collidersView = ecs.view<entity::Transform3DComponent, entity::ColliderComponent>();
        for (auto &&entity : collidersView) {
            auto&& [transform, collider] = collidersView.get(entity);

            switch (collider.GetColliderData().GetType()) {
                case entity::ColliderType::BOX: {
                    auto shape = collider.GetColliderData().Cast<entity::BoxColliderShape>();
                    BoxColliderDrawData data;
                    data.VertexShader = Asset::AssetHandle::Null;
                    data.FragmentShader = Asset::AssetHandle::Null;
                    data.TransformMatrix = transform.TransformMatrix; // process collider transform

                    frame.BoxColliders.push_back(data);
                    break;
                }

                case entity::ColliderType::SPHERE: {
                    auto shape = collider.GetColliderData().Cast<entity::SphereColliderShape>();
                    SphereColliderDrawData data;
                    data.VertexShader = Asset::AssetHandle::Null;
                    data.FragmentShader = Asset::AssetHandle::Null;
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
