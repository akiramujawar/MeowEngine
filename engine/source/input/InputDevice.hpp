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

        DoubleBuffer<InputEvents> GetEvents() const {
            return Buffer;
        }

    private:
        InputManager InputManager;

        /**
         * TODO: remove the dependency on SDL_Event (replace with messaging system)
         */
        DoubleBuffer<InputEvents> Buffer;
    };
}


#endif //MEOWENGINE_INPUTMODULE_HPP