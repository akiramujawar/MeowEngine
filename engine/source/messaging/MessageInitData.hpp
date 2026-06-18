//
// Created by Akira Mujawar on 10/06/26.
//

#ifndef MEOWENGINE_MESSAGEINITDATA_HPP
#define MEOWENGINE_MESSAGEINITDATA_HPP

namespace MeowEngine {
    namespace Editor {
        class Selector;
        class FileDialog;
    }

    namespace Runtime {
        class GameplaySystem;
    }

    namespace Asset {
        class AssetManager;
    }
}

namespace MeowEngine::Messaging {
    struct MessageInitData {
        Editor::Selector* Selector;
        Editor::FileDialog* FileDialog;

        Asset::AssetManager* AssetManager;
        Runtime::GameplaySystem* Gameplay;
    };
}

#endif //MEOWENGINE_MESSAGEINITDATA_HPP