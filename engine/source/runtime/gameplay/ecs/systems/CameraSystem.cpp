//
// Created by Akira Mujawar on 26/06/26.
//

#include "CameraSystem.hpp"

#include "CameraComponent.hpp"
#include "World.hpp"

namespace MeowEngine::Runtime {
    void CameraSystem::Update(Asset::World& world) {
        auto& camera = world.GetComponent<CameraComponent>(world.ActiveCamera);

        // make movements
        // camera.Configure();
        camera.UpdateMatrix();
    }
}
