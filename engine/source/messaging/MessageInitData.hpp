//
// Created by Akira Mujawar on 10/06/26.
//

#ifndef MEOWENGINE_MESSAGEINITDATA_HPP
#define MEOWENGINE_MESSAGEINITDATA_HPP

namespace MeowEngine {
    namespace Graphics {
        class GraphicsDevice;
    }

    namespace Editor {
        class Selector;
        class FileDialog;
    }

    namespace Runtime {
        class WorldManager;
        class GameplaySystem;
        class GameplayStateManager;
    }

    namespace Asset {
        class AssetManager;
    }

    namespace Physics {
        class PhysicsSystem;
    }
}

namespace MeowEngine::Messaging {
    struct MessageInitData {
        Graphics::GraphicsDevice* Device;

        Editor::Selector* Selector;
        Editor::FileDialog* FileDialog;

        Asset::AssetManager* AssetManager;
        Runtime::WorldManager* WorldManager;
        Runtime::GameplaySystem* Gameplay;
        Runtime::GameplayStateManager* GameplayStateManager;

        Physics::PhysicsSystem* Physics;
    };
}

#endif //MEOWENGINE_MESSAGEINITDATA_HPP