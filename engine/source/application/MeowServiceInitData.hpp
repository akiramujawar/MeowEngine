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
        class WorldManager;
    }

    namespace Messaging {
        class CommandQueue;
        class RequestQueue;
    }

    namespace Editor {
        class EditorModule;
    }

}

namespace MeowEngine {
    struct MeowServiceInitData {
        Asset::AssetManager& AssetManager;
        Runtime::Project& Project;
        Runtime::WorldManager& WorldManager;

        Messaging::CommandQueue& CommandQueue;
        Messaging::RequestQueue& RequestQueue;

        Editor::EditorModule& Editor;
    };
}

#endif //MEOWENGINE_MEOWSERVICEINITDATA_HPP