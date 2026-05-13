//
// Created by Akira Mujawar on 10/07/24.
//

#include <InputManager.hpp>
#include <SDL_mouse.h>

namespace MeowEngine::Runtime {

    void InputManager::ProcessInput() {
        // Update Mouse State
        mouseState = SDL_GetRelativeMouseState(&mouseDeltaX, &mouseDeltaY);
    }

    void InputManager::SetMouseDown() {
        isMouseDown = true;
    }

}