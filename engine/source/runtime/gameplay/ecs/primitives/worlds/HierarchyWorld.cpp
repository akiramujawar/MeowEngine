//
// Created by Akira Mujawar on 25/06/26.
//

#include "HierarchyWorld.hpp"


#include <Public/Math.hpp>
#include <Public/Core/Include.hpp>
#include <IdentityComponent.hpp>
#include <InfoComponent.hpp>

#include "HierarchyComponent.hpp"

namespace MeowEngine::Runtime {
    HierarchyWorld::HierarchyWorld() {
        CreateCamera();
        CreateHierarchy();
    }

    void HierarchyWorld::CreateCamera() {
        const auto entity = AddEntity();
        auto& info = GetComponent<Runtime::InfoComponent>(entity);
        // auto& transform = AddComponent<entity::Transform3DComponent>(entity);
        //
        // // tree.Self = entity;
        // info.SetName(String("[EDITOR] Camera"));
        // transform.Position = Vector3(10,20,300);
        // transform.Scale = Vector3(1,1,1);
        // transform.Euler = Vector3(1,10,2);
        // transform.Rotation = Quaternion(transform.Euler);

        // AddComponent<entity::CameraComponent>(
        //     cameraEntity
        // );
    }

    void HierarchyWorld::CreateHierarchy() {
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

    EntityHandle HierarchyWorld::CreateDefaultEntity(std::string name) {
        const auto entity = AddEntity();

        auto& info = GetComponent<Runtime::InfoComponent>(entity);
        // auto& tree = AddComponent<component::HierarchyComponent>(entity);

        info.SetName(String(name));
        // tree.Self = entity;

        return entity;
    }
}
