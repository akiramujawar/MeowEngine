//
// Created by Akira Mujawar on 09/06/26.
//

#ifndef MEOWENGINE_RENDERUIEXTRACTORINITDATA_HPP
#define MEOWENGINE_RENDERUIEXTRACTORINITDATA_HPP

namespace MeowEngine::Runtime {
    class GameplaySystem;
}

namespace MeowEngine::Editor {
    class Selector;
}

namespace MeowEngine::Rendering {
    struct RenderUIExtractorInitData {
        Runtime::GameplaySystem* Gameplay;
        Editor::Selector* Selector;
    };
}

#endif //MEOWENGINE_RENDERUIEXTRACTORINITDATA_HPP