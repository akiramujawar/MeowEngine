//
// Created by Akira Mujawar on 10/07/24.
//

#ifndef MEOWENGINE_INPUTMANAGER_HPP
#define MEOWENGINE_INPUTMANAGER_HPP

#include <InputEvents.hpp>

namespace MeowEngine::Input {
    class InputManager {
    public:
        InputManager(KeyboardState state);

        void ProcessDeviceInput(const InputEvents& events);

        /**
         * Should input manager be processed?
         * Yes, only if world view is focused on editor builds
         * otherwise true for sandbox release builds
         */
        bool IsActive;

        int MouseDeltaX;
        int MouseDeltaY;
        bool isMouseDown;

        MouseState MouseState;
        KeyboardState KeyState;
    };
}


#endif //MEOWENGINE_INPUTMANAGER_HPP
