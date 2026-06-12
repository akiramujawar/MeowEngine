//
// Created by Akira Mujawar on 19/05/26.
//

#ifndef MEOWENGINE_RENDEREXTRACTORINITDATA_HPP
#define MEOWENGINE_RENDEREXTRACTORINITDATA_HPP

namespace MeowEngine::Runtime {
    class GameplaySystem;
}

namespace MeowEngine::Editor {
    class Selector;
}

namespace MeowEngine::Rendering {
    struct RenderExtractorInitData {
        Runtime::GameplaySystem* Gameplay;
        Editor::Selector* Selector;
    };
}

#endif //MEOWENGINE_RENDEREXTRACTORINITDATA_HPP