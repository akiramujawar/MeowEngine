//
// Created by Akira Mujawar on 16/05/26.
//

#include <DefaultWorld.hpp>

#include <Public/Math.hpp>
#include <Public/Core.hpp>

#include <IdentityComponent.hpp>
#include <info_component.hpp>
#include <hierarchy_component.hpp>

#include <transform_handle_component.hpp>
#include <transform3d_component.hpp>
#include <camera_component.hpp>
#include <grid_component.hpp>
#include <sky_box_component.hpp>

namespace MeowEngine::Editor {
    DefaultWorld::DefaultWorld() {
        CreateCamera();
        CreateGrid();
        CreateSky();
        CreateTransformHandle();
    }

    DefaultWorld::~DefaultWorld() {}

    void DefaultWorld::CreateCamera() {
        const auto entity = AddEntity();
        auto& info = AddComponent<entity::InfoComponent>(entity);
        auto& identity = AddComponent<Runtime::IdentityComponent>(entity);
        auto& tree = AddComponent<component::HierarchyComponent>(entity);
        tree.Self = entity;

        info.SetName(String("Camera"));


        // AddComponent<entity::Transform3DComponent>(
        //     cameraEntity,
        //     Camera.GetProjectionMatrix() * Camera.GetViewMatrix(),
        //     Vector3{0, 0, 0},
        //     Vector3{1.0, 1.0f, 1.0f},
        //     glm::vec3{0.0f, 1.0f, 0.0f},
        //     0.0f
        // );
        // AddComponent<entity::CameraComponent>(
        //     cameraEntity
        // );
    }

    void DefaultWorld::CreateGrid() {
        const auto entity = AddEntity();
        auto& info = AddComponent<entity::InfoComponent>(entity);
        auto& identity = AddComponent<Runtime::IdentityComponent>(entity);
        auto& tree = AddComponent<component::HierarchyComponent>(entity);
        tree.Self = entity;
        info.SetName(String("Grid"));

        // AddComponent<entity::InfoComponent>(gridEntity, "Grid");
        // AddComponent<component::GridComponent>(
        //     gridEntity,
        //     assets::ShaderPipelineType::Grid
        // );
    }

    void DefaultWorld::CreateSky() {
        const auto entity = AddEntity();
        auto& info = AddComponent<entity::InfoComponent>(entity);
        auto& identity = AddComponent<Runtime::IdentityComponent>(entity);
        auto& tree = AddComponent<component::HierarchyComponent>(entity);
        tree.Self = entity;
        info.SetName(String("Sky Box"));

        // const auto skyEntity = AddEntity();
        // AddComponent<entity::InfoComponent>(skyEntity, "Sky Box");
        // AddComponent<entity::SkyBoxComponent>(
        //         skyEntity,
        //         assets::ShaderPipelineType::Sky
        // );
    }

    void DefaultWorld::CreateTransformHandle() {
        const auto entity = AddEntity();
        auto& info = AddComponent<entity::InfoComponent>(entity);
        auto& identity = AddComponent<Runtime::IdentityComponent>(entity);
        auto& tree = AddComponent<component::HierarchyComponent>(entity);
        tree.Self = entity;
        info.SetName(String("TransformHandle"));

        // AddComponent<entity::InfoComponent>(transformHandleEntity, "Transform Handle");
        // AddComponent<entity::TransformHandleComponent>(
        //     transformHandleEntity,
        //     assets::ShaderPipelineType::TRANSFORM_HANDLE
        // );
    }

}
