//
// Created by Akira Mujawar on 02/07/26.
//

#ifndef MEOWENGINE_INPUTDEVICEINIT_HPP
#define MEOWENGINE_INPUTDEVICEINIT_HPP

namespace MeowEngine::Messaging {
    class EventBus;
}

namespace MeowEngine::Input {
    struct InputDeviceInitData {
        Messaging::EventBus& EventBus;
    };
}

#endif //MEOWENGINE_INPUTDEVICEINIT_HPP