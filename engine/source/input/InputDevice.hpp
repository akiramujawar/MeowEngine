//
// Created by Akira Mujawar on 09/06/26.
//

#ifndef MEOWENGINE_INPUTMODULE_HPP
#define MEOWENGINE_INPUTMODULE_HPP

#include <vector>
#include <Public/Threading/Forward.hpp>

#include <InputEvents.hpp>
#include <InputManager.hpp>

namespace MeowEngine::Input {


    class InputDevice {
    public:
        InputDevice();
        ~InputDevice() = default;

        void Schedule(Threading::Scheduler& scheduler);

        InputManager& GetInputManager() { return InputManager; };
        InputEvents& GetEvents() { return InputEvents; };
        KeyboardState& GetKeyboardState() { return KeyState; };

    private:
        /**
         * TODO: remove the dependency on SDL_Event (replace with messaging system)
         */
        InputEvents InputEvents;
        KeyboardState KeyState;

        InputManager InputManager;
    };
}

// renderer -> add command queue for event -> add sdl event -> input device use the sdl event
// renderer -> add command queue -> input device do this
#endif //MEOWENGINE_INPUTMODULE_HPP