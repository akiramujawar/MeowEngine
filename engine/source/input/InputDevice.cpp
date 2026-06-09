//
// Created by Akira Mujawar on 09/06/26.
//

#include <InputDevice.hpp>
#include <log.hpp>
#include <Public/Threading/Include.hpp>

namespace MeowEngine::Input {

    InputDevice::InputDevice() {}

    InputDevice::~InputDevice() {}

    void InputDevice::Schedule(Threading::Scheduler& scheduler) {
        scheduler.AddTask(
            [&]() {
                Buffer.GetCurrent().clear();

                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    Buffer.GetCurrent().push_back(event);
                }
            }
        );

        scheduler.AddTask(
            [&]() {
                MeowEngine::Log("Input Count", static_cast<int>(Buffer.GetCurrent().size()));
                InputManager.ProcessDeviceInput(Buffer.GetCurrent());
            }
        );
    }

}
