//
// Created by Akira Mujawar on 15/06/26.
//

#ifndef MEOWENGINE_MEOWSERVICEINITDATA_HPP
#define MEOWENGINE_MEOWSERVICEINITDATA_HPP

// -- forwards -------------
namespace MeowEngine {
    namespace Asset {
        class AssetManager;
    }

    namespace Runtime {
        class Project;
    }

    namespace Editor {
        class EditorModule;
    }
}

namespace MeowEngine {
    struct MeowServiceInitData {
        Asset::AssetManager& AssetManager;
        Runtime::Project& Project;
        Editor::EditorModule& Editor;
    };
}

#endif //MEOWENGINE_MEOWSERVICEINITDATA_HPP