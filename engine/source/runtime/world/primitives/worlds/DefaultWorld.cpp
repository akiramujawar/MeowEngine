//
// Created by Akira Mujawar on 16/05/26.
//

#include <DefaultWorld.hpp>

#include <Public/Math.hpp>
#include <Public/Core/Include.hpp>

#include <IdentityComponent.hpp>
#include <InfoComponent.hpp>
#include <HierarchyComponent.hpp>

#include <TransformGizmoComponent.hpp>
#include <Transform3DComponent.hpp>
#include <CameraComponent.hpp>
#include <GridComponent.hpp>
#include <SkyBoxComponent.hpp>
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
        auto& identity = GetComponent<IdentityComponent>(entity);
        auto& info = GetComponent<Runtime::InfoComponent>(entity);
        auto& camera = AddComponent<Runtime::CameraComponent>(entity);

        info.SetName(String("[EDITOR] Camera"));
        camera.SetPosition(Vector3(0,10,-30));
        camera.SetRotation(Vector3(10,0,0));

        ActiveCamera = identity.GetEntityHandle();
    }

    void DefaultWorld::CreateGrid() {
        const auto entity = AddEntity();
        auto& identity = GetComponent<IdentityComponent>(entity);
        auto& info = GetComponent<Runtime::InfoComponent>(entity);
        AddComponent<Runtime::GridComponent>(entity);

        info.SetName(String("[Editor] Grid"));

        Grid = identity.GetEntityHandle();
    }

    void DefaultWorld::CreateSky() {
        const auto entity = AddEntity();
        auto& info = GetComponent<Runtime::InfoComponent>(entity);
        auto& identity = GetComponent<Runtime::IdentityComponent>(entity);
        AddComponent<Runtime::SkyBoxComponent>(entity);

        info.SetName(String("Sky Box"));

        SkyBox = identity.GetEntityHandle();
    }

    void DefaultWorld::CreateTransformHandle() {
        const auto entity = AddEntity();
        auto& info = GetComponent<Runtime::InfoComponent>(entity);
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
            auto& tree = GetComponent<Runtime::HierarchyComponent>(root1);
            tree.Self = root1;
            tree.FirstChild = root11;
        }

        {
            auto& tree = GetComponent<Runtime::HierarchyComponent>(root11);
            tree.Self = root11;
            tree.Parent = root1;
            tree.FirstChild = root111;
            tree.NextChildOfParent = root12;
        }

        {
            auto& tree = GetComponent<Runtime::HierarchyComponent>(root111);
            tree.Self = root111;
            tree.Parent = root11;
        }

        {
            auto& tree = GetComponent<Runtime::HierarchyComponent>(root12);
            tree.Self = root12;
            tree.Parent = root1;
            tree.FirstChild = root121;
            tree.PreviousChildOfParent = root11;
        }

        {
            auto& tree = GetComponent<Runtime::HierarchyComponent>(root121);
            tree.Self = root121;
            tree.Parent = root12;
        }
    }

    void DefaultWorld::CreateReflectionTest() {
        auto entity = CreateDefaultEntity("[TEST] Reflection");

        auto& reflection = AddComponent<Runtime::ReflectionTestComponent>(entity);
        reflection.Init();
    }

    void DefaultWorld::CreateEmptyLine() {
        CreateDefaultEntity("----------------------");
    }

    EntityHandle DefaultWorld::CreateDefaultEntity(std::string name) {
        const auto entity = AddEntity();
        auto& info = GetComponent<Runtime::InfoComponent>(entity);

        info.SetName(String(name));

        return entity;
    }

}
