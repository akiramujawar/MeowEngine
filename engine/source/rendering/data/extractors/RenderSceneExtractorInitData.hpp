//
// Created by Akira Mujawar on 19/05/26.
//

#ifndef MEOWENGINE_RENDERSCENEEXTRACTORINITDATA_HPP
#define MEOWENGINE_RENDERSCENEEXTRACTORINITDATA_HPP

// #include <GameplaySystem.hpp>
// #include <Selector.hpp>

namespace MeowEngine::Runtime {
    class GameplaySystem;
}

namespace MeowEngine::Editor {
    class Selector;
}

namespace MeowEngine::Rendering {
    struct RenderSceneExtractorInitData {
        Runtime::GameplaySystem* Gameplay;
        Editor::Selector* Selector;
    };
}

#endif //MEOWENGINE_RENDERSCENEEXTRACTORINITDATA_HPP