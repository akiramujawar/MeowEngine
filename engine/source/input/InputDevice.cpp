//
// Created by Akira Mujawar on 09/06/26.
//

#include <InputDevice.hpp>
#include <log.hpp>
#include <Public/Threading/Include.hpp>
#include "MeowService.hpp"
#include "EventBus.hpp"
#include "EventContainer.hpp"

namespace MeowEngine::Input {

    InputDevice::InputDevice()
        : KeyState(SDL_GetKeyboardState(nullptr))
        , InputManager(KeyState)
    {}

    void InputDevice::Init(const InputDeviceInitData& context) {
        InputManager.Init(KeyState, context.EventBus);
    }

    void InputDevice::SubscribeToEvents() {
        MeowService().EventBus.Subscribe<Messaging::SceneFocusEvent>(
           [&](const Messaging::SceneFocusEvent& event) {
               InputManager.SetEnableInput(event.IsFocus);
           }
       );
    }

    void InputDevice::Schedule(Threading::Scheduler& scheduler) {
        scheduler.AddTask(
            [&]() {
                PT_PROFILE_SCOPE_N("SDL Events");

                // Buffer.GetCurrent().clear();
                InputEvents.clear();

                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    InputEvents.push_back(event);
                }
            }
        );

        scheduler.AddTask(
            [&]() {
                PT_PROFILE_SCOPE_N("Input Manager");

                InputManager.ProcessDeviceInput(InputEvents);
            }
        );
    }

}
