//
// Created by Akira Mujawar on 10/06/26.
//

#ifndef MEOWENGINE_MESSAGECONTEXT_HPP
#define MEOWENGINE_MESSAGECONTEXT_HPP

namespace MeowEngine {
    namespace Editor {
        class Selector;
    }

    namespace Runtime {
        class GameplaySystem;
    }
}

namespace MeowEngine::Messaging {
    struct MessageContext {
        Editor::Selector* Selector;
        Runtime::GameplaySystem* Gameplay;
    };
}

#endif //MEOWENGINE_MESSAGECONTEXT_HPP