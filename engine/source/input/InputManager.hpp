//
// Created by Akira Mujawar on 10/07/24.
//

#ifndef MEOWENGINE_INPUTMANAGER_HPP
#define MEOWENGINE_INPUTMANAGER_HPP

#include <InputEvents.hpp>

namespace MeowEngine::Messaging {
    class EventBus;
}

namespace MeowEngine::Input {
    class InputManager {
        friend class InputDevice;

    public:
        InputManager(KeyboardState state);

        void Init(KeyboardState state, Messaging::EventBus& eventBus);
        void ProcessDeviceInput(const InputEvents& events);

        [[nodiscard]] bool GetIsEnabled() const { return IsActive; }

    private:
        void SetEnableInput(bool bIsEnable);

    public:
        int MouseDeltaX;
        int MouseDeltaY;
        bool isMouseDown;

        MouseState MouseState;
        KeyboardState KeyState;

    private:
        /**
         * Should input manager be processed?
         * Yes, only if world view is focused on editor builds
         * otherwise true for sandbox release builds
         */
        bool IsActive;

        Messaging::EventBus* EventBus;
    };
}


#endif //MEOWENGINE_INPUTMANAGER_HPP
