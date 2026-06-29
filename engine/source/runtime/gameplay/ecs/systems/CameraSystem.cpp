//
// Created by Akira Mujawar on 26/06/26.
//

#include "CameraSystem.hpp"

#include "CameraComponent.hpp"
#include "InputManager.hpp"
#include "MeowService.hpp"
#include "World.hpp"

namespace MeowEngine::Runtime {
    void CameraSystem::Update(Asset::World& world) {
        auto& camera = world.GetComponent<CameraComponent>(world.ActiveCamera);

        // make movements
        // camera.Configure();
        camera.UpdateMatrix();

        auto& inputManager =  MeowService().InputManager;
        if (inputManager.IsActive) {
            // mouse move
            if (inputManager.MouseState) {
                auto eulerAngles = camera.Local.GetEuler();
                eulerAngles.X += static_cast<float>(inputManager.MouseDeltaY) * camera.LookAroundSpeed; // vertical
                eulerAngles.Y += static_cast<float>(inputManager.MouseDeltaX) * camera.LookAroundSpeed; // horizontal

                camera.Local.SetRotation(eulerAngles);
            }

            // key move
            auto keyState = inputManager.KeyState;
            if (keyState[SDL_SCANCODE_UP] || keyState[SDL_SCANCODE_W]) {
                auto forward = camera.Local.GetForward();
                auto position = camera.Local.GetPosition();

                camera.Local.SetPosition(position + forward * camera.MoveSpeed);
            }

            if (keyState[SDL_SCANCODE_DOWN] || keyState[SDL_SCANCODE_S]) {
                auto forward = camera.Local.GetForward();
                auto position = camera.Local.GetPosition();

                camera.Local.SetPosition(position - forward * camera.MoveSpeed);
            }
        }
    }
}
