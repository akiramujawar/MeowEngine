//
// Created by Akira Mujawar on 12/06/26.
//

#ifndef MEOWENGINE_EDITORINITDATA_HPP
#define MEOWENGINE_EDITORINITDATA_HPP

namespace MeowEngine::Graphics {
    class GraphicsDevice;
}

namespace MeowEngine::Runtime {
    class ConfigManager;
}

namespace MeowEngine::Editor {
    struct EditorInitData {
        Graphics::GraphicsDevice* GraphicsDevice;
        Runtime::ConfigManager* Project;
    };
}

#endif //MEOWENGINE_EDITORINITDATA_HPP