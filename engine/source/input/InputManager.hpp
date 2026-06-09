//
// Created by Akira Mujawar on 10/07/24.
//

#ifndef MEOWENGINE_INPUTMANAGER_HPP
#define MEOWENGINE_INPUTMANAGER_HPP

#include <InputEvents.hpp>

namespace MeowEngine::Input {
    class InputManager {
    public:
        void ProcessDeviceInput(const InputEvents& events);

        bool isActive;
        uint32_t mouseState;
        int mouseDeltaX;
        int mouseDeltaY;
        bool isMouseDown;
    };
}


#endif //MEOWENGINE_INPUTMANAGER_HPP
