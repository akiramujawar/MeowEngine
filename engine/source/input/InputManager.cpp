//
// Created by Akira Mujawar on 10/07/24.
//

#include <InputManager.hpp>
#include <UserDeviceInputType.hpp>

namespace MeowEngine::Input {

    void InputManager::ProcessDeviceInput(const InputEvents& events) {
        // Reset
        isMouseDown = false;

        // Update Mouse State
        mouseState = SDL_GetRelativeMouseState(&mouseDeltaX, &mouseDeltaY);

        // process events
        for (const auto& event : events) {
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN: {
                    isMouseDown = true;
                    break;
                }
                case SDL_USEREVENT: {
                    switch (event.user.code) {
                        case UserDeviceInputType::WORLD_VIEW_FOCUS: {
                            isActive = *static_cast<bool*>(event.user.data1);
                            break;
                        }

                        default:
                            break;
                    }

                    break;
                }
                default:
                    break;
            }

        }
    }

}