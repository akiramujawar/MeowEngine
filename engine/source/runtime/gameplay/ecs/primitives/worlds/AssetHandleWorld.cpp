//
// Created by Akira Mujawar on 25/06/26.
//

#include "AssetHandleWorld.hpp"

#include <Public/Math.hpp>
#include <Public/Core/Include.hpp>

#include <info_component.hpp>
#include "grid_component.hpp"


namespace MeowEngine::Runtime {
    AssetHandleWorld::AssetHandleWorld() {
        CreateCamera();
        CreateEmtpy("Hello");
    }

    void AssetHandleWorld::CreateCamera() {
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

    void AssetHandleWorld::CreateEmtpy(const std::string& name) {
        const auto entity = AddEntity();
        auto& info = GetComponent<Runtime::InfoComponent>(entity);

        AddComponent<GridComponent>(entity);

        info.SetName(String(name));
    }



}