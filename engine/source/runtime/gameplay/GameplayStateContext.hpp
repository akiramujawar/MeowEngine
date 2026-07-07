//
// Created by Akira Mujawar on 06/07/26.
//

#ifndef MEOWENGINE_GAMEPLAYSTATECONTEXT_HPP
#define MEOWENGINE_GAMEPLAYSTATECONTEXT_HPP

namespace MeowEngine::Messaging {
    class CommandQueue;
}

namespace MeowEngine::Runtime {
    class WorldManager;
    class GameplaySystem;

    struct GameplayStateContext {
        WorldManager* WorldManager;
        GameplaySystem* Gameplay;
        Messaging::CommandQueue* CommandQueue;
    };
}

#endif //MEOWENGINE_GAMEPLAYSTATECONTEXT_HPP