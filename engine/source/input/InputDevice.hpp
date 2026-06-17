//
// Created by Akira Mujawar on 09/06/26.
//

#ifndef MEOWENGINE_INPUTMODULE_HPP
#define MEOWENGINE_INPUTMODULE_HPP

#include <vector>
#include <SDL_API.hpp>
#include <double_buffer.hpp>

#include <Public/Threading/Forward.hpp>

#include <InputEvents.hpp>
#include <InputManager.hpp>

namespace MeowEngine::Input {


    class InputDevice {
    public:
        InputDevice();
        ~InputDevice();

        void Schedule(Threading::Scheduler& scheduler);

        // DoubleBuffer<InputEvents> GetEvents() const {
        //     return Buffer;
        // }
        InputEvents& GetEvents() { return InputEvents; };

    private:
        InputManager InputManager;

        /**
         * TODO: remove the dependency on SDL_Event (replace with messaging system)
         */
        InputEvents InputEvents;
    };
}

// renderer -> add command queue for event -> add sdl event -> input device use the sdl event
// renderer -> add command queue -> input device do this
#endif //MEOWENGINE_INPUTMODULE_HPP