//
// Created by Akira Mujawar on 12/06/26.
//

#ifndef MEOWENGINE_EDITORINITCONTEXT_HPP
#define MEOWENGINE_EDITORINITCONTEXT_HPP

namespace MeowEngine::Graphics {
    class GraphicsDevice;
}

namespace MeowEngine::Editor {
    struct EditorInitContext {
          Graphics::GraphicsDevice* GraphicsDevice;
    };
}

#endif //MEOWENGINE_EDITORINITCONTEXT_HPP