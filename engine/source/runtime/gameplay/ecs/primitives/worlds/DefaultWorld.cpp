//
// Created by Akira Mujawar on 16/05/26.
//

#include <DefaultWorld.hpp>

#include <Public/Math.hpp>
#include <Public/Core/Include.hpp>

#include <IdentityComponent.hpp>
#include <info_component.hpp>
#include <hierarchy_component.hpp>

#include <transform_handle_component.hpp>
#include <transform3d_component.hpp>
#include <camera_component.hpp>
#include <grid_component.hpp>
#include <sky_box_component.hpp>
#include <reflection_test_component.hpp>

namespace MeowEngine::Runtime {
    DefaultWorld::DefaultWorld() {
        // editor entities
        CreateEmptyLine();
        CreateCamera();
        CreateTransformHandle();
        CreateGrid();

        // test entities
        CreateEmptyLine();
        CreateHierarchyTest();
        CreateReflectionTest();

        // runtime entities
        CreateEmptyLine();
        CreateSky();
    }

    DefaultWorld::~DefaultWorld() {}

    void DefaultWorld::CreateCamera() {
        const auto entity = AddEntity();
        auto& info = GetComponent<entity::InfoComponent>(entity);
        // auto& tree = AddComponent<component::HierarchyComponent>(entity);
        auto& transform = AddComponent<entity::Transform3DComponent>(entity);

        // tree.Self = entity;
        info.SetName(String("[EDITOR] Camera"));
        transform.Position = Vector3(10,20,300);
        transform.Scale = Vector3(1,1,1);
        transform.Euler = Vector3(1,10,2);
        transform.Rotation = Quaternion(transform.Euler);

        // AddComponent<entity::CameraComponent>(
        //     cameraEntity
        // );
    }

    void DefaultWorld::CreateGrid() {
        const auto entity = AddEntity();
        auto& info = GetComponent<entity::InfoComponent>(entity);
        // auto& tree = AddComponent<component::HierarchyComponent>(entity);
        // tree.Self = entity;
        info.SetName(String("[Editor] Grid"));

        // AddComponent<component::GridComponent>(
        //     gridEntity,
        //     assets::ShaderPipelineType::Grid
        // );
    }

    void DefaultWorld::CreateSky() {
        const auto entity = AddEntity();
        auto& info = GetComponent<entity::InfoComponent>(entity);
        // auto& tree = AddComponent<component::HierarchyComponent>(entity);
        // tree.Self = entity;
        info.SetName(String("Sky Box"));

        // AddComponent<entity::SkyBoxComponent>(
        //         skyEntity,
        //         assets::ShaderPipelineType::Sky
        // );
    }

    void DefaultWorld::CreateTransformHandle() {
        const auto entity = AddEntity();
        auto& info = GetComponent<entity::InfoComponent>(entity);
        // auto& tree = AddComponent<component::HierarchyComponent>(entity);
        // tree.Self = entity;
        info.SetName(String("[EDITOR] TransformHandle"));

        // AddComponent<entity::TransformHandleComponent>(
        //     transformHandleEntity,
        //     assets::ShaderPipelineType::TRANSFORM_HANDLE
        // );
    }

    void DefaultWorld::CreateHierarchyTest() {
        const auto root1 = CreateDefaultEntity("[TEST] Hierarchy");
        const auto root11 = CreateDefaultEntity("Child11");
        const auto root111 = CreateDefaultEntity("Child111");
        const auto root12 = CreateDefaultEntity("Child12");
        const auto root121 = CreateDefaultEntity("Child121");

        {
            auto& tree = GetComponent<component::HierarchyComponent>(root1);
            tree.Self = root1;
            tree.FirstChild = root11;
        }

        {
            auto& tree = GetComponent<component::HierarchyComponent>(root11);
            tree.Self = root11;
            tree.Parent = root1;
            tree.FirstChild = root111;
            tree.NextChildOfParent = root12;
        }

        {
            auto& tree = GetComponent<component::HierarchyComponent>(root111);
            tree.Self = root111;
            tree.Parent = root11;
        }

        {
            auto& tree = GetComponent<component::HierarchyComponent>(root12);
            tree.Self = root12;
            tree.Parent = root1;
            tree.FirstChild = root121;
            tree.PreviousChildOfParent = root11;
        }

        {
            auto& tree = GetComponent<component::HierarchyComponent>(root121);
            tree.Self = root121;
            tree.Parent = root12;
        }
    }

    void DefaultWorld::CreateReflectionTest() {
        auto entity = CreateDefaultEntity("[TEST] Reflection");

        auto& reflection = AddComponent<entity::ReflectionTestComponent>(entity);
        reflection.Init();
    }

    void DefaultWorld::CreateEmptyLine() {
        CreateDefaultEntity("----------------------");
    }

    EntityHandle DefaultWorld::CreateDefaultEntity(std::string name) {
        const auto entity = AddEntity();

        auto& info = GetComponent<entity::InfoComponent>(entity);
        // auto& tree = AddComponent<component::HierarchyComponent>(entity);

        info.SetName(String(name));
        // tree.Self = entity;

        return entity;
    }

}
