//
// Created by Akira Mujawar on 10/07/24.
//

#include <InputManager.hpp>
#include <UserDeviceInputType.hpp>

namespace MeowEngine::Input {
    InputManager::InputManager(KeyboardState state)
        : IsActive(false)
        , MouseState(0)
        , MouseDeltaX(0)
        , MouseDeltaY(0)
        , isMouseDown(false)
        , KeyState(state)
    {}

    void InputManager::ProcessDeviceInput(const InputEvents& events) {
        // Reset
        isMouseDown = false;

        // Update Mouse State
        MouseState = SDL_GetRelativeMouseState(&MouseDeltaX, &MouseDeltaY);

        // process events
        for (const auto& event : events) {
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN: {
                    isMouseDown = true;
                    break;
                }
                // TODO: move this to command queue
                case SDL_USEREVENT: {
                    auto userEvent = static_cast<UserDeviceInputType>(event.user.code);
                    switch (userEvent) {
                        case UserDeviceInputType::WORLD_VIEW_FOCUS: {
                            IsActive = *static_cast<bool*>(event.user.data1);
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