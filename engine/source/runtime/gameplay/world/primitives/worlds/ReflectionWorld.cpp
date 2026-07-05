//
// Created by Akira Mujawar on 22/06/26.
//

#include "ReflectionWorld.hpp"

#include <Public/Math.hpp>
#include <Public/Core/Include.hpp>
#include <IdentityComponent.hpp>
#include <InfoComponent.hpp>

namespace MeowEngine::Runtime {
    ReflectionWorld::ReflectionWorld() {
        CreateCamera();
        CreateEmtpy("Hello");
        CreateReflectionTest();
    }
    ReflectionWorld::~ReflectionWorld() {}

    void ReflectionWorld::CreateCamera() {
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

    void ReflectionWorld::CreateEmtpy(std::string name) {
        const auto entity = AddEntity();
        auto& info = GetComponent<Runtime::InfoComponent>(entity);

        info.SetName(String(name));
    }

    void ReflectionWorld::CreateReflectionTest() {

    }

}
