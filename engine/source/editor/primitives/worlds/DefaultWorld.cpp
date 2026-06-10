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
        CreateHierarchyTest();
    }

    DefaultWorld::~DefaultWorld() {}

    void DefaultWorld::CreateCamera() {
        const auto entity = AddEntity();
        auto& info = AddComponent<entity::InfoComponent>(entity);
        auto& identity = AddComponent<Runtime::IdentityComponent>(entity);
        auto& tree = AddComponent<component::HierarchyComponent>(entity);
        tree.Self = entity;

        info.SetName(String("[EDITOR] Camera"));


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
        info.SetName(String("[EDITOR] TransformHandle"));

        // AddComponent<entity::TransformHandleComponent>(
        //     transformHandleEntity,
        //     assets::ShaderPipelineType::TRANSFORM_HANDLE
        // );
    }

    void DefaultWorld::CreateHierarchyTest() {
        const auto root1 = CreateDefaultEntity();
        const auto root11 = CreateDefaultEntity();
        const auto root111 = CreateDefaultEntity();
        const auto root12 = CreateDefaultEntity();
        const auto root121 = CreateDefaultEntity();

        {
            auto& info = GetComponent<entity::InfoComponent>(root1);
            auto& tree = GetComponent<component::HierarchyComponent>(root1);
            info.SetName(String("[TEST] Hierarchy"));
            tree.Self = root1;
            tree.FirstChild = root11;
        }

        {
            auto& info = GetComponent<entity::InfoComponent>(root11);
            auto& tree = GetComponent<component::HierarchyComponent>(root11);
            info.SetName(String("Child11"));
            tree.Self = root11;
            tree.Parent = root1;
            tree.FirstChild = root111;
            tree.NextChildOfParent = root12;
        }

        {
            auto& info = GetComponent<entity::InfoComponent>(root111);
            auto& tree = GetComponent<component::HierarchyComponent>(root111);
            info.SetName(String("Child111"));
            tree.Self = root111;
            tree.Parent = root11;
        }

        {
            auto& info = GetComponent<entity::InfoComponent>(root12);
            auto& tree = GetComponent<component::HierarchyComponent>(root12);
            info.SetName(String("Child12"));
            tree.Self = root12;
            tree.Parent = root1;
            tree.FirstChild = root121;
            tree.PreviousChildOfParent = root11;
        }

        {
            auto& info = GetComponent<entity::InfoComponent>(root121);
            auto& tree = GetComponent<component::HierarchyComponent>(root121);
            info.SetName(String("Child121"));
            tree.Self = root121;
            tree.Parent = root12;
        }
    }

    entt::entity DefaultWorld::CreateDefaultEntity() {
        const auto entity = AddEntity();

        AddComponent<entity::InfoComponent>(entity);
        AddComponent<Runtime::IdentityComponent>(entity);
        auto& tree = AddComponent<component::HierarchyComponent>(entity);
        tree.Self = entity;

        return entity;
    }
}
